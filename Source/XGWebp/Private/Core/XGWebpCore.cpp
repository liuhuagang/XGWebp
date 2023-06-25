// Copyright Xiao Gang. All Rights Reserved.
#include "XGWebpCore.h"
#include "iostream"
#include "vector"
#include "Slate/SceneViewport.h"
#include "XGWebpLib.h"
#include "Engine/GameViewportClient.h"
#include "Engine/World.h"
#include "Misc/Paths.h"
#include "Log/LogXGWebp.h"
PRAGMA_DISABLE_OPTIMIZATION

bool FXGWebpCore::GenerateStaticWebpPicture(FString& InPicturePath,
	TArray<FColor>& InPictureColors,
	FVector2D& InPictureSize,
	int32           InQualityFactor /*= 100*/)
{
	if (!CheckWebpPicturePath(InPicturePath))
	{
		return false;
	}
	if (InPictureColors.Num() != InPictureSize.X * InPictureSize.Y)
	{
		UE_LOG(LogXGWebp, Display, TEXT("FXGWebpCore::GenerateStaticWebpPicture Wrong ColorsNum"));
		return false;
	}


	const char* OutPicturePath = TCHAR_TO_ANSI(*InPicturePath);

	unsigned char* Data = new unsigned char[InPictureColors.Num() * 4 + 1];
	memset(Data, 0, InPictureColors.Num() * 4 + 1);
	int i = 0;
	for (auto& Tmp : InPictureColors)
	{
		Data[i] = Tmp.R;
		i++;
		Data[i] = Tmp.G;
		i++;
		Data[i] = Tmp.B;
		i++;
		Data[i] = 255 - Tmp.A;
		i++;
	}
	InQualityFactor = FMath::Clamp(InQualityFactor, 0, 100);

	bool Result = FXGWebpLibStruct::GenerateWebpByRGBA(OutPicturePath,
		Data,
		InPictureSize.X,
		InPictureSize.Y,
		InQualityFactor);

	delete[] Data;
	Data = nullptr;

	return Result;
}

bool FXGWebpCore::GenerateDynamicWebpPicture(FString& InPicturePath, TSharedPtr<FXGWebpPictureInformation> InWebpPictureInformation, TArray<TArray<FColor>>& InPicturesColors, TArray<int32>& WebpTimestepMillisecond, int32 InQualityFactor /*= 100*/)
{
	if (!CheckWebpPicturePath(InPicturePath))
	{
		return false;
	}
	for (auto& InPictureColors : InPicturesColors)
	{
		if (InPictureColors.Num() != InWebpPictureInformation->GetPictureWidth() * InWebpPictureInformation->GetPictureHeight())
		{
			return false;
		}
	}
	if (InPicturesColors.Num() != WebpTimestepMillisecond.Num())
	{
		return false;
	}



	const char* OutPicturePath = TCHAR_TO_ANSI(*InPicturePath);
	std::vector<const unsigned char*> Datas;
	for (auto& InPictureColors : InPicturesColors)
	{
		unsigned char* Data = new unsigned char[InPictureColors.Num() * 4 + 1];
		memset(Data, 0, InPictureColors.Num() * 4 + 1);
		int i = 0;
		for (auto& Tmp : InPictureColors)
		{
			Data[i] = Tmp.R;
			i++;
			Data[i] = Tmp.G;
			i++;
			Data[i] = Tmp.B;
			i++;
			Data[i] = Tmp.A;
			i++;
		}

		Datas.push_back(Data);
	}

	std::vector<int> Timestamps;
	for (auto& InTimestamp : WebpTimestepMillisecond)
	{
		Timestamps.push_back(InTimestamp);
	}
	InQualityFactor = FMath::Clamp(InQualityFactor, 0, 100);

	bool Result = FXGWebpLibStruct::GenerateDymaicWebpByRGBA(
		OutPicturePath,
		Datas,
		Timestamps,
		InWebpPictureInformation->GetPictureWidth(),
		InWebpPictureInformation->GetPictureHeight(),
		InQualityFactor);


	for (auto& Data : Datas)
	{
		delete[] Data;
		Data = nullptr;
	}


	return Result;
}

bool FXGWebpCore::LoadDynamicWebpPicture(FString& InWebpFilePath, TArray<int32>& OutWebpTimestepMillisecond, TArray<TArray<FColor>>& OutPicturesColors, TSharedPtr<FXGWebpPictureInformation> OutWebpPictureInformation)
{

	const char* InWebpFilePath_ANSI = TCHAR_TO_ANSI(*InWebpFilePath);
	std::vector<const unsigned char*> OutRGBADatas;
	std::vector<int> OutTimestamps_ms;
	int OutWidth = -1; 
	int OutHeight = -1;
	bool bLoadWebp = FXGWebpLibStruct::LoadDynamicWebpPictureByRGBA(InWebpFilePath_ANSI, OutRGBADatas, OutTimestamps_ms, OutWidth, OutHeight);

	return bLoadWebp;
}

bool FXGWebpCore::GetViewportSize(UObject* WorldContextObject, FVector2D& OutViewportSize)
{
	if (!WorldContextObject || !WorldContextObject->GetWorld())
	{
		return false;

	}


	if (UGameViewportClient* InViewportClient = WorldContextObject->GetWorld()->GetGameViewport())
	{
		if (FSceneViewport* InViewport = InViewportClient->GetGameViewport())
		{
			OutViewportSize = FVector2D::ZeroVector;
			InViewportClient->GetViewportSize(OutViewportSize);
			return true;
		}
	}

	return false;
}

bool FXGWebpCore::CheckWebpPicturePath(FString& InGeneratedWebpPicturesPath)
{
	FString Extension = FPaths::GetExtension(InGeneratedWebpPicturesPath);
	FString Directory = FPaths::GetPath(InGeneratedWebpPicturesPath);

	if (Extension.Equals(TEXT("webp")) && FPaths::DirectoryExists(Directory))
	{
		return true;
	}
	UE_LOG(LogXGWebp, Warning, TEXT("FXGWebpCore::CheckWebpPicturePath Wrong Path"));
	return false;
}

bool FXGWebpCore::CheckInWebpPictureSize(UObject* WorldContextObject, TSharedPtr<FXGWebpPictureInformation> InWebpPictureInformation)
{
	if (!WorldContextObject || !WorldContextObject->GetWorld())
	{
		return false;

	}
	FVector2D ViewportSize;
	if (GetViewportSize(WorldContextObject, ViewportSize))
	{
		bool	bX0 = InWebpPictureInformation->X0 >= 0 && InWebpPictureInformation->X0 < InWebpPictureInformation->X1;
		bool	bX1 = InWebpPictureInformation->X1 <= ViewportSize.X;

		bool	bY0 = InWebpPictureInformation->Y0 >= 0 && InWebpPictureInformation->Y0 < InWebpPictureInformation->Y1;
		bool	bY1 = InWebpPictureInformation->Y1 <= ViewportSize.Y;

		if (bX0 && bX1 && bY0 && bY1)
		{
			return true;
		}
	}
	UE_LOG(LogXGWebp, Warning, TEXT("FXGWebpCore::CheckInWebpPictureSize Wrong WebpPictureSize"));
	return false;
}





PRAGMA_ENABLE_OPTIMIZATION