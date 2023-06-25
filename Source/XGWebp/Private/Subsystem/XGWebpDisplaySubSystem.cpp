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
	TArray<TArray<FColor>> OutPicturesColors;
	TSharedPtr<FXGWebpPictureInformation> OutWebpPictureInformation =MakeShared<FXGWebpPictureInformation>();

	//此处需要异步
	bool bLoadWebp= FXGWebpCore::LoadDynamicWebpPicture(InWebpFilePath, OutWebpTimestepMillisecond, OutPicturesColors, OutWebpPictureInformation);




}


