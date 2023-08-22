// Copyright Xiao Gang. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "XGWebpType.h"
#include "Tickable.h"
#include "Engine/Texture2D.h"
#include "XGWebpDisplaySubSystem.generated.h"



/**
 * Internal use,maybe you can use FXGwebpCore API or XGWebpLibrary.
 */
UCLASS()
class  UXGWebpDisplaySubSystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	friend class UXGWebpBPLibrary;
	
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
	
	UFUNCTION()
	void LoadWebp(FString InWebpFilePath);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTexture2D* WebpTexture;


	bool bShowWebp =false;
	int32 WebpShowIndex=-1;
	int32 CurrentMillisecond=-1;
	TArray<int32> WebpTimestepMillisecond;
	TArray<TArray<FColor>> PicturesColors;
	int32 WebpWidth = 0;
	int32 WebpHeight = 0;




};