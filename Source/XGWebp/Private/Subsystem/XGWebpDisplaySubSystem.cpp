// Copyright Xiao Gang. All Rights Reserved.
#include "XGWebpDisplaySubSystem.h"
#include "XGWebpCore.h"
#include "Engine/World.h"
#include "Async/Async.h"

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
	Super::Deinitialize();

}

void UXGWebpDisplaySubSystem::Tick(float DeltaTime)
{

	DeltaTime*=1000;
	if (bShowWebp&& WebpTexture)
	{	//TODO,cost much
		for (int32 WebpIndex = 0;WebpIndex< WebpTimestepMillisecond.Num();WebpIndex++)
		{
			 if (WebpIndex==0&& CurrentMillisecond < WebpTimestepMillisecond[WebpIndex])
			 {
				 CurrentMillisecond+= DeltaTime;
				 WebpShowIndex = WebpIndex;
				 break;
			 }

			 if (WebpIndex == WebpTimestepMillisecond.Num()-1 && CurrentMillisecond > WebpTimestepMillisecond[WebpIndex])
			 {
				 CurrentMillisecond=0;
				 WebpShowIndex = WebpIndex;
				 break;
			 }

			 if (CurrentMillisecond> WebpTimestepMillisecond[WebpIndex])
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

void UXGWebpDisplaySubSystem::LoadWebp(FString InWebpFilePath)
{



	//此处需要异步
	bool bLoadWebp = FXGWebpCore::LoadDynamicWebpPicture(InWebpFilePath, WebpTimestepMillisecond, PicturesColors, WebpWidth, WebpHeight);

	if (bLoadWebp)
	{
		bShowWebp=true;
		WebpTexture = UTexture2D::CreateTransient(WebpWidth, WebpHeight, EPixelFormat::PF_R8G8B8A8);

		uint8* textureData = static_cast<uint8*>(WebpTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
		FMemory::Memcpy(textureData, PicturesColors[0].GetData(), WebpWidth * WebpHeight * 4);
		WebpShowIndex =0;
		WebpTexture->PlatformData->Mips[0].BulkData.Unlock();
		WebpTexture->UpdateResource();

		int32 aa21 =1;
	}









}


