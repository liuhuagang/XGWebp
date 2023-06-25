// Copyright Xiao Gang. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "XGWebpType.h"
#include "XGWebpLibrary.generated.h"

/**
 * Provide to use C++ API
 */
UCLASS()
class XGWEBP_API UXGWebpLibrary : public UObject
{
	GENERATED_BODY()

public:

	static	bool BeginRecord(UObject* WorldContextObject, FString InGeneratedWebpPicturesPath, FXGWebpPictureInformation InWebpPictureInformation);

	static	bool BeginRecordFullViewport(UObject* WorldContextObject, FString InGeneratedWebpPicturesPath);

	static	void EndRecord(UObject* WorldContextObject, FSimpleDelegate InFinisnWebpDelegate = FSimpleDelegate(), FXGWebpFinishGenerateWebp InFinshWebpBPDelegate = FXGWebpFinishGenerateWebp());

	static	void LoadWebp(UObject* WorldContextObject, FString InWebpFilePath);

};