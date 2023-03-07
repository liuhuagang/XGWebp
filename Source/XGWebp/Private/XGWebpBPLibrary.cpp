// Copyright Xiao Gang. All Rights Reserved.
#include "XGWebpBPLibrary.h"
#include "XGWebpLibrary.h"

void UXGWebpBPLibrary::BeginRecord(
	UObject* WorldContextObject,
	FString InGeneratedWebpPicturesPath,
	FXGWebpPictureInformation InWebpPictureInformation,
	bool& bBegin)
{
	bBegin = UXGWebpLibrary::BeginRecord(WorldContextObject, InGeneratedWebpPicturesPath, InWebpPictureInformation);
}

void UXGWebpBPLibrary::BeginRecordFullViewport(
	UObject* WorldContextObject,
	FString InGeneratedWebpPicturesPath,
	bool& bBegin)
{
	bBegin = UXGWebpLibrary::BeginRecordFullViewport(WorldContextObject, InGeneratedWebpPicturesPath);
}

void UXGWebpBPLibrary::EndRecord(
	UObject* WorldContextObject,
	FXGWebpFinishGenerateWebp InFinishWebpBPDegelete)
{
	UXGWebpLibrary::EndRecord(WorldContextObject, FSimpleDelegate(), InFinishWebpBPDegelete);
}

