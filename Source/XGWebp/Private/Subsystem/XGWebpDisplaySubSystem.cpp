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

	TArray<int32> OutWebpTimestepMillisecond;
	TArray<uint8*> OutPicturesColors;
	int32 WebpWidth = 0;
	int32 WebpHeight = 0;

	//此处需要异步
	bool bLoadWebp= FXGWebpCore::LoadDynamicWebpPicture(InWebpFilePath, OutWebpTimestepMillisecond, OutPicturesColors, WebpWidth, WebpHeight);

	
	
		WebpTexture =	UTexture2D::CreateTransient(WebpWidth, WebpHeight, EPixelFormat::PF_R8G8B8A8);

	


		uint8* textureData = static_cast<uint8*>(WebpTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
		FMemory::Memcpy(textureData ,OutPicturesColors[10], WebpWidth * WebpHeight * 4);

		WebpTexture->PlatformData->Mips[0].BulkData.Unlock();
		WebpTexture->UpdateResource();



		


}


