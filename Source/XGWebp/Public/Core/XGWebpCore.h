// Copyright 2023 XiaoGang 
#pragma once


#include "CoreMinimal.h"
#include "XGWebpType.h"

class  FXGWebpCore : public UObject
{
public:
    static bool GenerateStaticWebpPicture(FString& InPicturePath,
        TArray<FColor>& InPictureColors,
        FVector2D& InPictureSize,
        int32           InQualityFactor = 100);

	static bool GenerateDynamicWebpPicture(
        FString& InPicturePath,
        TSharedPtr<FXGWebpPictureInformation> InWebpPictureInformation,
		TArray<TArray<FColor>>& InPicturesColors,
        TArray<int32>& WebpTimestepMillisecond,
		int32                   InQualityFactor = 100);




public:

    static	bool CheckWebpPicturePath(FString& InGeneratedWebpPicturesPath);
    static	bool GetViewportSize(UObject* WorldContextObject, FVector2D& OutViewportSize);
    static	bool CheckInWebpPictureSize(UObject* WorldContextObject, TSharedPtr<FXGWebpPictureInformation> InWebpPictureInformation);





};