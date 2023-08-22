// Copyright Xiao Gang. All Rights Reserved.
#include "XGWebpBPLibrary.h"
#include "Subsystem/XGWebpMangeSubSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Core/XGWebpCore.h"
#include "Subsystem/XGWebpDisplaySubSystem.h"

void UXGWebpBPLibrary::BeginRecord(
	UObject* WorldContextObject,
	FString InGeneratedWebpPicturesPath,
	FXGWebpPictureInformation InWebpPictureInformation,
	bool& bBegin)
{
	bBegin =false;

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

	TSharedPtr<FXGWebpPictureInformation> XGWebpPictureInformationPtr = MakeShareable(new FXGWebpPictureInformation(InWebpPictureInformation));


	bBegin=	XGWebpMangeSubSystem->BeginRecord(InGeneratedWebpPicturesPath, XGWebpPictureInformationPtr);

}

void UXGWebpBPLibrary::BeginRecordFullViewport(
	UObject* WorldContextObject,
	FString InGeneratedWebpPicturesPath,
	bool& bBegin)
{
	bBegin =false;

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

	FVector2D ViewportSize;

	if (FXGWebpCore::GetViewportSize(WorldContextObject, ViewportSize))
	{
		TSharedPtr<FXGWebpPictureInformation> WebpPictureInformation = MakeShareable(new FXGWebpPictureInformation(0, 0, ViewportSize.X - 1, ViewportSize.Y - 1));
		bBegin=XGWebpMangeSubSystem->BeginRecord(InGeneratedWebpPicturesPath, WebpPictureInformation);
	}

	


}

void UXGWebpBPLibrary::EndRecord(
	UObject* WorldContextObject,
	FXGWebpFinishGenerateWebp InFinishWebpBPDegelete)
{
	if (!WorldContextObject)
	{
		return;
	}
	if (!WorldContextObject->GetWorld())
	{
		return;
	}

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	UXGWebpMangeSubSystem* XGWebpMangeSubSystem = GameInstance->GetSubsystem<UXGWebpMangeSubSystem>();

	XGWebpMangeSubSystem->EndRecord(InFinishWebpBPDegelete);


}

void UXGWebpBPLibrary::LoadWebp(UObject* WorldContextObject, FString InWebpFilePath)
{
	if (!WorldContextObject)
	{
		return;
	}
	if (!WorldContextObject->GetWorld())
	{
		return;
	}

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	UXGWebpDisplaySubSystem* XGWebpDisplaySubSystem = GameInstance->GetSubsystem<UXGWebpDisplaySubSystem>();

	XGWebpDisplaySubSystem->LoadWebp(InWebpFilePath);
}

