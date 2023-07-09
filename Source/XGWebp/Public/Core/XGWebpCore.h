// Copyright Xiao Gang. All Rights Reserved.
#pragma once


#include "CoreMinimal.h"
#include "XGWebpType.h"
/** You can use this class. Those method is designed to interact with UEC++. */
class  XGWEBP_API FXGWebpCore : public UObject
{
public:

	/** Just one picture within webp */
	static bool GenerateStaticWebpPicture(FString& InPicturePath,
		TArray<FColor>& InPictureColors,
		FVector2D& InPictureSize,
		int32           InQualityFactor = 100);

	/** Many pictures within webp */
	static bool GenerateDynamicWebpPicture(
		FString& InPicturePath,
		TSharedPtr<FXGWebpPictureInformation> InWebpPictureInformation,
		TArray<TArray<FColor>>& InPicturesColors,
		TArray<int32>& WebpTimestepMillisecond,
		int32                   InQualityFactor = 100);


	/** Many pictures within webp */
	static bool LoadDynamicWebpPicture
	(
		FString& InWebpFilePath,
		TArray<int32>& OutWebpTimestepMillisecond,
		TArray<TArray<FColor>>& OutPicturesColors,
		int32& OutWebpWidth, 
		int32& OutWebpHeight
	);




public:
	static	bool CheckWebpPicturePath(FString& InGeneratedWebpPicturesPath);
	static	bool GetViewportSize(UObject* WorldContextObject, FVector2D& OutViewportSize);
	static	bool CheckInWebpPictureSize(UObject* WorldContextObject, TSharedPtr<FXGWebpPictureInformation> InWebpPictureInformation);





};