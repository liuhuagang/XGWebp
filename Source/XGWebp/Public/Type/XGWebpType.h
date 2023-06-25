// Copyright 2023 Xiao Gang. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "XGWebpType.generated.h"




DECLARE_DYNAMIC_DELEGATE_OneParam(FXGWebpFinishGenerateWebp,bool,bFinishGenerate);

USTRUCT(BlueprintType)
struct XGWEBP_API FXGWebpPictureInformation 
{
	GENERATED_USTRUCT_BODY()
public:
	FXGWebpPictureInformation();
	FXGWebpPictureInformation(int32 InX0,int32 InY0,int32 InX1,int32 InY1);
	FXGWebpPictureInformation(FXGWebpPictureInformation& InWebpPictureInformation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGWebp")
		int32 X0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGWebp")
		int32 Y0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGWebp")
		int32 X1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XGWebp")
		int32 Y1;

	int32 GetPictureWidth();
	int32 GetPictureHeight();

	void ResetPictureInformation();
};


UENUM()
enum class EXGWebpProcessType :uint8
{
	None,
	Recording,
	Generating,
	Max
};