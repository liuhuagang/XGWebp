// Copyright Xiao Gang. All Rights Reserved.
#include "XGWebpDisplaySubSystem.h"
#include "XGWebpCore.h"
#include "Engine/World.h"
#include "Async/Async.h"

UXGWebpDisplaySubSystem::UXGWebpDisplaySubSystem()
{
}

bool UXGWebpDisplaySubSystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return true;

}

void UXGWebpDisplaySubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);




}

void UXGWebpDisplaySubSystem::Deinitialize()
{
	ReleaseLoadedWebp();
	Super::Deinitialize();

}

void UXGWebpDisplaySubSystem::Tick(float DeltaTime)
{
	if (LoadAndShowStatus == EXGWebpLoadAndShowType::Showing && WebpTexture)
	{
		DeltaTime *= 1000;
		//TODO,cost much
		for (int32 WebpIndex = 0; WebpIndex < WebpTimestepMillisecond.Num(); WebpIndex++)
		{
			if (WebpIndex == 0 && CurrentMillisecond < WebpTimestepMillisecond[WebpIndex])
			{
				CurrentMillisecond += DeltaTime;
				WebpShowIndex = WebpIndex;
				break;
			}

			if (WebpIndex == WebpTimestepMillisecond.Num() - 1 && CurrentMillisecond > WebpTimestepMillisecond[WebpIndex])
			{
				CurrentMillisecond = 0;
				WebpShowIndex = WebpIndex;
				break;
			}

			if (CurrentMillisecond > WebpTimestepMillisecond[WebpIndex])
			{
				continue;
			}

			CurrentMillisecond += DeltaTime;
			WebpShowIndex = WebpIndex;

			break;

		}

		/*
				int32 DataSize = sizeof(FColor);
				FUpdateTextureRegion2D  UpdateRegion;
				UpdateRegion.SrcX=0;
				UpdateRegion.SrcY = 0;
				UpdateRegion.DestX = 0;
				UpdateRegion.DestY = 0;
				UpdateRegion.Width = WebpWidth;
				UpdateRegion.Height = WebpHeight;

				WebpTexture->UpdateTextureRegions(0, 1, &UpdateRegion,  WebpWidth* DataSize, DataSize,(uint8*)PicturesColors[WebpShowIndex].GetData());

		*/


		uint8* textureData = static_cast<uint8*>(WebpTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
		FMemory::Memcpy(textureData, PicturesColors[WebpShowIndex].GetData(), WebpWidth * WebpHeight * 4);

		WebpTexture->PlatformData->Mips[0].BulkData.Unlock();
		WebpTexture->UpdateResource();

	}

}

TStatId UXGWebpDisplaySubSystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UXGWebpDisplaySubSystem, STATGROUP_Tickables);
}

bool UXGWebpDisplaySubSystem::IsTickable() const
{
	return !IsTemplate();
}

void UXGWebpDisplaySubSystem::LoadWebp
(FXGWebpLoadAndShowWebp InLoadAndShowEbpDegelete,
	FString InWebpFilePath)
{

	bool bRightPath = FXGWebpCore::CheckWebpPicturePath(InWebpFilePath);
	bool bRgihtStatus = LoadAndShowStatus ==EXGWebpLoadAndShowType::None;
	if (!bRightPath|| !bRgihtStatus)
	{
		InLoadAndShowEbpDegelete.ExecuteIfBound(false, nullptr, 0, 0);
	}



	LoadAndShowStatus = EXGWebpLoadAndShowType::Loading;
	XGWebpLoadAndShowWebp = InLoadAndShowEbpDegelete;

	UXGWebpDisplaySubSystem* XGWebpDisplaySubSystem = this;

	AsyncTask(ENamedThreads::AnyThread,[InWebpFilePath,this, XGWebpDisplaySubSystem](){
	
		//此处需要异步
		bool bLoadWebp = FXGWebpCore::LoadDynamicWebpPicture(InWebpFilePath, WebpTimestepMillisecond, PicturesColors, WebpWidth, WebpHeight);

		//此处需要返回主线程
		AsyncTask(ENamedThreads::GameThread,[bLoadWebp, XGWebpDisplaySubSystem](){
		
			XGWebpDisplaySubSystem->LoadedWebpCallShow(bLoadWebp);

		});

		
	
	
	});



}

void UXGWebpDisplaySubSystem::ReleaseLoadedWebp()
{
	switch (LoadAndShowStatus)
	{
	case EXGWebpLoadAndShowType::None:
		break;
	case EXGWebpLoadAndShowType::Loading:

		AsyncTask(ENamedThreads::GameThread,[this](){
		
			ReleaseLoadedWebp();
		
		});

		break;
	case EXGWebpLoadAndShowType::Showing:
		
		LoadAndShowStatus = EXGWebpLoadAndShowType::None;
		WebpTexture = nullptr;
		WebpShowIndex = -1;
		CurrentMillisecond = -1;
		WebpWidth = 0;
		WebpHeight = 0;
		WebpTimestepMillisecond.Empty();
		for (auto& Tmp : PicturesColors)
		{
			Tmp.Empty();
		}
		PicturesColors.Empty();

		break;
	case EXGWebpLoadAndShowType::Max:
		break;
	default:
		break;
	}

}

void UXGWebpDisplaySubSystem::LoadedWebpCallShow(bool bLoaded)
{

	if (bLoaded)
	{
		LoadAndShowStatus=EXGWebpLoadAndShowType::Showing;

		WebpTexture = UTexture2D::CreateTransient(WebpWidth, WebpHeight, EPixelFormat::PF_R8G8B8A8);
		uint8* textureData = static_cast<uint8*>(WebpTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
		FMemory::Memcpy(textureData, PicturesColors[0].GetData(), WebpWidth * WebpHeight * 4);
		WebpShowIndex = 0;
		WebpTexture->PlatformData->Mips[0].BulkData.Unlock();
		WebpTexture->UpdateResource();
		XGWebpLoadAndShowWebp.ExecuteIfBound(true, WebpTexture, WebpWidth, WebpHeight);
	}
	else
	{
		LoadAndShowStatus = EXGWebpLoadAndShowType::None;
		XGWebpLoadAndShowWebp.ExecuteIfBound(false, nullptr, 0, 0);


	}

}


