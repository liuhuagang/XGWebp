// Copyright Xiao Gang. All Rights Reserved.
#pragma once


#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XGWebpType.h"
#include "XGWebpBPLibrary.generated.h"


/** Interacte with Blurpint API */
UCLASS()
class XGWEBP_API UXGWebpBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:


	/**
	 * BeginRecord every frame data within specific viewport pixel coordinate
	 * @param	WorldContextObject
	 * @param	InGeneratedWebpPicturesPath		The Path will be used to save.Such as : "D:/Webp/XgPicture.webp".
	 *											The directory must be established.Path can not be root directory.Such as :"D:/xgPicture.webp"
	 *											The extension must end with ".webp"
	 * @param	InWebpPictureInformation		(X0,Y0)->(X1,Y1)If you want to get the pictrue size with 600x600,you can input (0,0) and (599,599)
	 *											If you want to get the center of viewport picture with 600x600,when Screen Size is 1920x1080,maybe
	 *											you can input (660,240) and(1259,839).Becasue our viewport size is 1920x1080.but it starts with (0,0),
	 *											end with (1919,1079).
	 * @param	bBegin							Whether to succeed to begin Recording Webp
	 * @return	
	 */
	UFUNCTION(BlueprintCallable, Category = "XGWebp", meta = (WorldContext = "WorldContextObject",DisplayName="BeginRecord"))
		static	void BeginRecord(
		UObject* WorldContextObject, 
		FString InGeneratedWebpPicturesPath, 
		FXGWebpPictureInformation InWebpPictureInformation,
		bool& bBegin);


	/**
	 * BeginRecord every frame date with full viewport size
	 * @param	WorldContextObject
	 * @param	InGeneratedWebpPicturesPath		The Path will be used to save.Such as : "D:/Webp/XgPicture.webp".
	 *											The directory must be established.Path can not be root directory.Such as :"D:/xgPicture.webp"
	 *											The extension must end with ".webp"
	 * @param	bBegin							Whether to succeed to begin Recording Webp
	 * @return	
	 */
	UFUNCTION(BlueprintCallable, Category = "XGWebp", meta = (WorldContext = "WorldContextObject",DisplayName = "BeginRecordFullViewport"))
		static	void BeginRecordFullViewport(
		UObject* WorldContextObject, 
		FString InGeneratedWebpPicturesPath,
		bool& bBegin);

	/**
	 * End to record date ,Then to generate Webp.It may be long time,so it is async.please wait to call back from InFinishWebpBPDegelete.
	 * @param	WorldContextObject
	 * @param	InFinishWebpBPDegelete			When gerating webp is finished,call InFinishWebpBPDegelete to execute.
	 * @return	
	 */
	UFUNCTION(BlueprintCallable, Category = "XGWebp", meta = (WorldContext = "WorldContextObject", DisplayName = "EndRecord"))
		static	void EndRecord(UObject* WorldContextObject, FXGWebpFinishGenerateWebp InFinishWebpBPDegelete);


	/**
	 * @brief	
	 * @param	
	 * @return	
	 */
	UFUNCTION(BlueprintCallable, Category = "XGWebp", meta = (WorldContext = "WorldContextObject",DisplayName = "LoadWebp"))
	static	void LoadWebp(UObject* WorldContextObject, FString InWebpFilePath);



};