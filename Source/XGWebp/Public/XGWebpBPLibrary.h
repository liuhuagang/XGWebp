// Copyright 2023 XiaoGang 
#pragma once


#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Core/XGWebpType.h"
#include "XGWebpBPLibrary.generated.h"



UCLASS()
class XGWEBP_API UXGWebpBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:


	 /**
	  * BeginRecord every frame data within specific viewport pixel coordinate
	  * @param	WorldContextObject				
	  * @param	InGeneratedWebpPicturesPath		The Path will be used to save.Such as : "D:/Webp/XgPicture.webp".
	  *											The directory must be established.The extension must end with ".webp"
	  * @param	InWebpPictureInformation		(X0,Y0)->(X1,Y1)If you want to get the pictrue size with 600x600,you can input (0,0) and (599,599)
												If you want to get the center of viewport picture with 600x600,when Screen Size is 1920x1080,maybe
												you can input (660,240) and(1259,839) 
	  * @return	Whether to succeed to begin Recording Webp
	  */
	UFUNCTION(BlueprintCallable, Category="XGWebp", meta = (WorldContext = "WorldContextObject"))
	static	bool BeginRecord(UObject* WorldContextObject, FString InGeneratedWebpPicturesPath, FXGWebpPictureInformation InWebpPictureInformation);

	UFUNCTION(BlueprintCallable, Category = "XGWebp", meta = (WorldContext = "WorldContextObject"))
	static	bool BeginRecordFullViewport(UObject* WorldContextObject, FString InGeneratedWebpPicturesPath);

	UFUNCTION(BlueprintCallable, Category = "XGWebp", meta = (WorldContext = "WorldContextObject"))
	static	void EndRecord(UObject* WorldContextObject, FXGWebpFinishGenerateWebp InFinishWebpBPDegelete);






};