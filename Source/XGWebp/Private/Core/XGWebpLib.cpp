// Copyright Xiao Gang. All Rights Reserved.
#define _CRT_SECURE_NO_WARNINGS
#include "XGWebpLib.h"
#include "iostream"
#include "CoreMinimal.h"
#if PLATFORM_WINDOWS
#include "XGWebpLibrary/mux.h"
#include "XGWebpLibrary/encode.h"
#include "XGWebpLibrary/decode.h"
#include "XGWebpLibrary/demux.h"
#endif





bool FXGWebpLibStruct::GenerateWebpByRGBA(const char* InWebpSavePath,
	const unsigned char* InRGBAData,
	int                  InWidth,
	int                  InHeight,
	float                InQualityFactor)
{
#if PLATFORM_WINDOWS
	if (InQualityFactor < 0)
	{
		InQualityFactor = 0;
	}
	if (InQualityFactor > 100)
	{
		InQualityFactor = 100;
	}

	uint8_t* Output = nullptr;
	size_t   Size = WebPEncodeRGBA(InRGBAData, InWidth, InHeight, InWidth * 4, 100.f, &Output);
	if (Size == 0)
	{
		return false;
	}


	FILE* FDes = fopen(InWebpSavePath, "wb");
	if (FDes)
	{
		fwrite(Output, Size, 1, FDes);
		fclose(FDes);
		return true;
	}
	WebPFree(Output);
#endif

	return false;
}



bool FXGWebpLibStruct::GenerateDymaicWebpByRGBA(const char* InWebpSavePath,
	std::vector<const unsigned char*>& InRGBADatas,
	std::vector<int>                   InTimestamps_ms,
	int                                InWidth,
	int                                InHeight,
	float InQualityFactor /*= 100*/)
{
#if PLATFORM_WINDOWS
	if (InQualityFactor < 0)
	{
		InQualityFactor = 0;
	}
	if (InQualityFactor > 100)
	{
		InQualityFactor = 100;
	}
	if (InTimestamps_ms.size() != InRGBADatas.size())
	{
		return false;
	}
	WebPConfig WebpPictureConfig;
	if (!WebPConfigInit(&WebpPictureConfig))
	{
		return false;
	}

	WebPAnimEncoderOptions EncodeOptions;

	if (!WebPAnimEncoderOptionsInit(&EncodeOptions))
	{
		return false;
	}


	EncodeOptions.kmin = 0;
	EncodeOptions.kmax = 1;
	WebpPictureConfig.lossless = 0;
	WebpPictureConfig.method = 4;
	WebpPictureConfig.quality = InQualityFactor;

	WebPAnimEncoderOptions Enc_options;
	if (!WebPAnimEncoderOptionsInit(&Enc_options))
	{
		return false;
	}

	WebPAnimEncoder* Encoder = WebPAnimEncoderNew(InWidth, InHeight, &Enc_options);
	if (!Encoder)
	{
		return false;
	}
	float                                       TimePoint = 0.f;
	std::vector<const unsigned char*>::iterator DataItem = InRGBADatas.begin();
	std::vector<int>::iterator                  TimeStepItem = InTimestamps_ms.begin();
	for (; DataItem != InRGBADatas.end(); ++DataItem, ++TimeStepItem)
	{
		WebPPicture WebpOneFramePicture;
		WebPPictureInit(&WebpOneFramePicture);
		WebpOneFramePicture.use_argb = 1;
		WebpOneFramePicture.width = InWidth;
		WebpOneFramePicture.height = InHeight;
		WebpOneFramePicture.argb_stride = InWidth * 4;
		WebPPictureImportRGBA(&WebpOneFramePicture, *DataItem, InWidth * 4);
		TimePoint += *TimeStepItem;
		WebPAnimEncoderAdd(Encoder, &WebpOneFramePicture, TimePoint, &WebpPictureConfig);
		WebPPictureFree(&WebpOneFramePicture);
	}
	WebPAnimEncoderAdd(Encoder, NULL, TimePoint, NULL);
	WebPData WebpPictureData;
	WebPAnimEncoderAssemble(Encoder, &WebpPictureData);
	WebPAnimEncoderDelete(Encoder);



	FILE* FDes = fopen(InWebpSavePath, "wb");
	if (FDes)
	{
		fwrite(WebpPictureData.bytes, WebpPictureData.size, 1, FDes);
		fclose(FDes);

		WebPDataClear(&WebpPictureData);

		return true;
	}
	WebPDataClear(&WebpPictureData);

#endif
	return false;
}

bool FXGWebpLibStruct::LoadDynamicWebpPictureByRGBA(const char* InWebpFilePath, std::vector<const unsigned char*>& OutRGBADatas, std::vector<int>& OutTimestamps_ms, int& OutWidth, int& OutHeight )
{
#if PLATFORM_WINDOWS
	bool bSucceed = true;
	FILE* FFileSource = fopen(InWebpFilePath, "rb");
	if (!FFileSource)
	{
		bSucceed = false;
		return bSucceed;
	}
	unsigned char* FileOriginalData;
	unsigned int   FileLength;
	fseek(FFileSource, 0, SEEK_END);
	FileLength = ftell(FFileSource);
	FileOriginalData = (unsigned char*) WebPMalloc(FileLength);
	memset(FileOriginalData, 0, FileLength );
	fseek(FFileSource, 0, SEEK_SET);
	fread(FileOriginalData, FileLength, 1, FFileSource);
	fclose(FFileSource);

	WebPData               OriginWebpData = { FileOriginalData, (size_t)FileLength };


	WebPAnimDecoderOptions DecOptions;
	WebPAnimDecoderOptionsInit(&DecOptions);

	WebPAnimDecoder* Decoder = WebPAnimDecoderNew(&OriginWebpData, &DecOptions);
	WebPAnimInfo     AnimInfo;
	WebPAnimDecoderGetInfo(Decoder, &AnimInfo);
	
	OutWidth = AnimInfo.canvas_width;
	OutHeight = AnimInfo.canvas_height;
	OutRGBADatas.clear();
	OutTimestamps_ms.clear();


	int framNum = 0;
	int Timestamp = 0;

	while (WebPAnimDecoderHasMoreFrames(Decoder))
	{
		uint8_t* buf;

		WebPAnimDecoderGetNext(Decoder, &buf, &Timestamp);
		framNum++;
		
		unsigned char* oneWebpColorData = (unsigned char*) malloc(OutWidth * OutHeight*4);
		memset(oneWebpColorData,0, OutWidth * OutHeight * 4);
		memcpy(oneWebpColorData,buf , OutWidth * OutHeight * 4);

		OutRGBADatas.push_back(oneWebpColorData);
		OutTimestamps_ms.push_back(Timestamp);





	}
	WebPAnimDecoderReset(Decoder);
	WebPAnimDecoderDelete(Decoder);



	WebPDataClear(&OriginWebpData);

#endif






	return bSucceed;
}

bool FXGWebpLibStruct::ResizeDynamicWebp(const char* InResizedWebpPath,
	const char* InWebpSavePath,
	int         InResizeWidth,
	int         InResizeHight,
	int         InQualityFactor /*= 100*/)
{
#if PLATFORM_WINDOWS

	bool bSucceed = true;
	if (InResizeWidth <= 0 || InResizeHight <= 0)
	{
		bSucceed = false;
		return bSucceed;
	}
	if (InQualityFactor < 0)
	{
		InQualityFactor = 0;
	}
	if (InQualityFactor > 100)
	{
		InQualityFactor = 100;
	}



	FILE* FFileSource = fopen(InResizedWebpPath, "rb");
	if (!FFileSource)
	{
		bSucceed = false;
		return bSucceed;
	}
	unsigned char* FileOriginalData;
	unsigned int   FileLength;
	fseek(FFileSource, 0, SEEK_END);
	FileLength = ftell(FFileSource);
	FileOriginalData = new unsigned char[FileLength + 1];
	memset(FileOriginalData, 0, FileLength + 1);
	fseek(FFileSource, 0, SEEK_SET);
	fread(FileOriginalData, FileLength, 1, FFileSource);
	fclose(FFileSource);


	WebPData               OriginWebpData = { FileOriginalData, (size_t)FileLength };
	WebPAnimDecoderOptions DecOptions;
	WebPAnimDecoderOptionsInit(&DecOptions);

	WebPAnimDecoder* Decoder = WebPAnimDecoderNew(&OriginWebpData, &DecOptions);
	WebPAnimInfo     AnimInfo;
	WebPAnimDecoderGetInfo(Decoder, &AnimInfo);


	WebPConfig Config;
	WebPConfigInit(&Config);

	WebPAnimEncoderOptions EncOptions;
	WebPAnimEncoderOptionsInit(&EncOptions);

	EncOptions.kmin = 0;
	EncOptions.kmax = 1;
	Config.lossless = 0;
	Config.method = 4;
	Config.quality = (float)InQualityFactor;

	WebPAnimEncoder* Encoder = WebPAnimEncoderNew(InResizeWidth, InResizeHight, &EncOptions);



	int framNum = 0;
	int Timestamp = 0;
	while (WebPAnimDecoderHasMoreFrames(Decoder))
	{
		uint8_t* buf;

		WebPAnimDecoderGetNext(Decoder, &buf, &Timestamp);
		int OriginHeight = AnimInfo.canvas_height;
		int OriginWidth = AnimInfo.canvas_width;

		WebPPicture Picture;
		WebPPictureInit(&Picture);
		Picture.use_argb = 1;
		Picture.width = OriginWidth;
		Picture.height = OriginHeight;
		Picture.argb_stride = OriginWidth * 4;
		WebPPictureAlloc(&Picture);
		WebPPictureImportRGBA(&Picture, buf, OriginWidth * 4);
		WebPPictureRescale(&Picture, InResizeWidth, InResizeHight);
		WebPAnimEncoderAdd(Encoder, &Picture, Timestamp, &Config);
		WebPPictureFree(&Picture);
		framNum++;
	}
	WebPAnimDecoderReset(Decoder);
	WebPAnimDecoderDelete(Decoder);

	WebPAnimEncoderAdd(Encoder, NULL, Timestamp, NULL);

	WebPData WebpData;
	WebPAnimEncoderAssemble(Encoder, &WebpData);
	WebPAnimEncoderDelete(Encoder);


	FILE* FDes = fopen(InWebpSavePath, "wb");
	if (FDes)
	{
		fwrite(WebpData.bytes, WebpData.size, 1, FDes);
		fclose(FDes);
	}
	else
	{
		bSucceed = false;
	}


	//to fix
	WebPDataClear(&OriginWebpData);
	WebPDataClear(&WebpData);

	return bSucceed;


#endif
	return false;
}

