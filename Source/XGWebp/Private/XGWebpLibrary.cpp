// Copyright Xiao Gang. All Rights Reserved.
#include "XGWebpLibrary.h"
#include "XGWebpMangeSubSystem.h"
#include "Kismet/GameplayStatics.h"
#include "XGWebpCore.h"

bool UXGWebpLibrary::BeginRecord(UObject* WorldContextObject, FString InGeneratedWebpPicturesPath, FXGWebpPictureInformation InWebpPictureInformation)
{
	if (!WorldContextObject)
	{
		return false;
	}
	if (!WorldContextObject->GetWorld())
	{
		return false;
	}

	UGameInstance* GameInstance =	UGameplayStatics::GetGameInstance(WorldContextObject);
	UXGWebpMangeSubSystem* XGWebpMangeSubSystem =	GameInstance->GetSubsystem<UXGWebpMangeSubSystem>();

	TSharedPtr<FXGWebpPictureInformation> XGWebpPictureInformationPtr=  MakeShareable(new FXGWebpPictureInformation(InWebpPictureInformation));


	return	XGWebpMangeSubSystem->BeginRecord(InGeneratedWebpPicturesPath, XGWebpPictureInformationPtr);
}

bool UXGWebpLibrary::BeginRecordFullViewport(UObject* WorldContextObject, FString InGeneratedWebpPicturesPath)
{
	if (!WorldContextObject)
	{
		return false;
	}
	if (!WorldContextObject->GetWorld())
	{
		return false;
	}

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	UXGWebpMangeSubSystem* XGWebpMangeSubSystem = GameInstance->GetSubsystem<UXGWebpMangeSubSystem>();

	FVector2D ViewportSize ;
	if (FXGWebpCore::GetViewportSize(WorldContextObject, ViewportSize))
	{
		TSharedPtr<FXGWebpPictureInformation> WebpPictureInformation = MakeShareable(new FXGWebpPictureInformation(0,0, ViewportSize.X-1, ViewportSize.Y-1));
		return	XGWebpMangeSubSystem->BeginRecord(InGeneratedWebpPicturesPath, WebpPictureInformation);
	}

	return false;

}

void UXGWebpLibrary::EndRecord(UObject* WorldContextObject, FSimpleDelegate InFinisnWebpDelegate, FXGWebpFinishGenerateWebp InFinshWebpBPDelegate)
{
	if (!WorldContextObject)
	{
		return ;
	}
	if (!WorldContextObject->GetWorld())
	{
		return ;
	}

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	UXGWebpMangeSubSystem* XGWebpMangeSubSystem = GameInstance->GetSubsystem<UXGWebpMangeSubSystem>();

	XGWebpMangeSubSystem->EndRecord(InFinisnWebpDelegate, InFinshWebpBPDelegate);
}

void UXGWebpLibrary::LoadWebp(UObject* WorldContextObject, FString InWebpFilePath)
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	UXGWebpDisplaySubSystem* XGWebpDisplaySubSystem = GameInstance->GetSubsystem<UXGWebpDisplaySubSystem>();

	XGWebpDisplaySubSystem->LoadWebp(InWebpFilePath);
}

