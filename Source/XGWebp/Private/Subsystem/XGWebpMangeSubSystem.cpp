// Copyright Xiao Gang. All Rights Reserved.
#include "XGWebpMangeSubSystem.h"
#include "XGWebpCore.h"
#include "Engine/World.h"
#include "Async/Async.h"
#include "Log/LogXGWebp.h"
bool UXGWebpMangeSubSystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return true;

}

void UXGWebpMangeSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	GenerateWebpCallBackDelegate.BindUFunction(this, "GenerateWebpCallBack");
	WebpPictureInformation = MakeShareable(new FXGWebpPictureInformation);
}

void UXGWebpMangeSubSystem::Deinitialize()
{
	Super::Deinitialize();
	GenerateWebpCallBackDelegate.Unbind();
	ResetRecord();
}

void UXGWebpMangeSubSystem::Tick(float DeltaTime)
{
	if (ProcessType == EXGWebpProcessType::Recording)
	{
		RecordOneFrame(DeltaTime);
	}

}

TStatId UXGWebpMangeSubSystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UXGWebpMangeSubSystem, STATGROUP_Tickables);
}

bool UXGWebpMangeSubSystem::IsTickable() const
{
	return !IsTemplate();
}

bool UXGWebpMangeSubSystem::BeginRecord(FString& InGeneratedWebpPicturesPath, TSharedPtr< FXGWebpPictureInformation> InWebpPictureInformation)
{
	if (!GetWorld())
	{
		return false;
	}
	if (ProcessType != EXGWebpProcessType::None)
	{
		return false;
	}
	if (!FXGWebpCore::CheckInWebpPictureSize(GetWorld(), InWebpPictureInformation))
	{
		return false;
	}
	if (!FXGWebpCore::CheckWebpPicturePath(InGeneratedWebpPicturesPath))
	{
		return false;
	}
	ResetRecord();
	ProcessType = EXGWebpProcessType::Recording;
	GeneratedWebpPicturesPath = InGeneratedWebpPicturesPath;
	WebpPictureInformation = InWebpPictureInformation;
	FlushRenderingCommands();

	ScreenHandle = UGameViewportClient::OnScreenshotCaptured().AddUObject(this,
		&UXGWebpMangeSubSystem::ScreenShotCallback);

	return true;
}

void UXGWebpMangeSubSystem::RecordOneFrame(float DeltaTime)
{
	FScreenshotRequest::RequestScreenshot(false);
	if (WebpTimestepMillisecond.Num() == 0)
	{
		WebpTimestepMillisecond.Add(0);
	}
	else
	{
		WebpTimestepMillisecond.Add(DeltaTime * 1000);
	}

}

void UXGWebpMangeSubSystem::EndRecord(FSimpleDelegate& InFinisnWebpDelegate, FXGWebpFinishGenerateWebp& InFinshWebpBPDelegate)
{
	if (ProcessType != EXGWebpProcessType::Recording)
	{
		return;
	}
	ProcessType = EXGWebpProcessType::Generating;
	FinisnWebpDelegate = InFinisnWebpDelegate;
	FinshWebpBPDelegate = InFinshWebpBPDelegate;



	AsyncTask(ENamedThreads::AnyThread, [&]()
		{
			FPlatformProcess::Sleep(0.2);
			FScopeLock XGLock(&XGWebpMutex);

	bool GenerateWebp = FXGWebpCore::GenerateDynamicWebpPicture(
		GeneratedWebpPicturesPath,
		WebpPictureInformation,
		WebPColor,
		WebpTimestepMillisecond
	);

	AsyncTask(ENamedThreads::GameThread, [&, GenerateWebp]() {

		GenerateWebpCallBackDelegate.ExecuteIfBound(GenerateWebp);

		});
		}
	);
}

void UXGWebpMangeSubSystem::GenerateWebpCallBack(bool bGenerateWebp)
{
	if (ScreenHandle.IsValid())
	{
		UGameViewportClient::OnScreenshotCaptured().Remove(ScreenHandle);
	}

	FinisnWebpDelegate.ExecuteIfBound();
	FinshWebpBPDelegate.ExecuteIfBound(bGenerateWebp);
	ResetRecord();
}

void UXGWebpMangeSubSystem::ResetRecord()
{

	ProcessType = EXGWebpProcessType::None;
	if (ScreenHandle.IsValid())
	{
		UGameViewportClient::OnScreenshotCaptured().Remove(ScreenHandle);
	}
	GeneratedWebpPicturesPath = TEXT("");
	WebpPictureInformation->ResetPictureInformation();
	WebPColor.Empty();
	WebpTimestepMillisecond.Empty();


}



void UXGWebpMangeSubSystem::ScreenShotCallback(int32 InWidth, int32 InHeight, const TArray<FColor>& InColors)
{

	AsyncTask(ENamedThreads::AnyThread, [&, InWidth, InHeight, InColors]() {


		FScopeLock XGLock(&XGWebpMutex);

	TArray<FColor> OutColors;
	for (int32 IndexY = 1; IndexY <= InHeight; IndexY++)
	{
		for (int32 IndexX = 1; IndexX <= InWidth; IndexX++)
		{

			int32 IndexXY = (IndexY - 1) * InWidth + IndexX;

			int32 IndexArray = IndexXY - 1;
			bool  bIndexX = (IndexX >= WebpPictureInformation->X0 + 1) && (IndexX <= WebpPictureInformation->X1 + 1);
			bool  bIndexY = (IndexY >= WebpPictureInformation->Y0 + 1) && (IndexY <= WebpPictureInformation->Y1 + 1);
			if (bIndexX && bIndexY)
			{
				OutColors.Add(InColors[IndexArray]);
			}
		}
	}
	if (OutColors.Num() == (WebpPictureInformation->X1 - WebpPictureInformation->X0 + 1) * (WebpPictureInformation->Y1 - WebpPictureInformation->Y0 + 1))
	{
		WebPColor.Add(OutColors);
		return;
	}


		});



}

