// Copyright Xiao Gang. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "XGWebpType.h"
#include "Tickable.h"
#include "XGWebpDisplaySubSystem.generated.h"



/**
 * Internal use,maybe you can use FXGwebpCore API or XGWebpLibrary.
 */
UCLASS()
class  UXGWebpDisplaySubSystem : public UGameInstanceSubsystem, public FTickableGameObject
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
	
	UFUNCTION()
	void LoadWebp(FString InWebpFilePath);



};