// Copyright Xiao Gang. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "XGWebpType.h"
#include "Tickable.h"
#include "XGWebpMangeSubSystem.generated.h"

DECLARE_DELEGATE_OneParam(FGenerateWebpCallBack,bool)

/**
 * Internal use,maybe you can use FXGwebpCore API or XGWebpLibrary.
 */
UCLASS()
class  UXGWebpMangeSubSystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	friend class UXGWebpLibrary;
	
	GENERATED_BODY()
public:


	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:


	virtual void    Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual bool    IsTickable() const override;

protected:
	bool BeginRecord(FString& InGeneratedWebpPicturesPath, TSharedPtr< FXGWebpPictureInformation> InWebpPictureInformation);
	void RecordOneFrame(float DeltaTime);
	void EndRecord(FSimpleDelegate& InFinisnWebpDelegate, FXGWebpFinishGenerateWebp& InFinshWebpBPDelegate);
	UFUNCTION()
	void GenerateWebpCallBack(bool bGenerateWebp);
	void ResetRecord();



protected:
	UFUNCTION()
		void ScreenShotCallback(int32 InWidth, int32 InHeight, const TArray<FColor>& InColors);

private:

	EXGWebpProcessType ProcessType;
	FString GeneratedWebpPicturesPath;
	TSharedPtr< FXGWebpPictureInformation> 	 WebpPictureInformation;

	FDelegateHandle ScreenHandle;
	TArray<TArray<FColor>> WebPColor;
	TArray<int32> WebpTimestepMillisecond;
	FGenerateWebpCallBack GenerateWebpCallBackDelegate;
	FSimpleDelegate FinisnWebpDelegate;
	FXGWebpFinishGenerateWebp FinshWebpBPDelegate;

	FCriticalSection XGWebpMutex;
};