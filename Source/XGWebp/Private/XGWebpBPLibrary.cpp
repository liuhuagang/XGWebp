// Copyright 2023 XiaoGang 
#include "XGWebpBPLibrary.h"
#include "XGWebpLibrary.h"

bool UXGWebpBPLibrary::BeginRecord(UObject* WorldContextObject,FString InGeneratedWebpPicturesPath, FXGWebpPictureInformation InWebpPictureInformation)
{
	return UXGWebpLibrary::BeginRecord(WorldContextObject,InGeneratedWebpPicturesPath, InWebpPictureInformation);
}

bool UXGWebpBPLibrary::BeginRecordFullViewport(UObject* WorldContextObject, FString InGeneratedWebpPicturesPath)
{
	return UXGWebpLibrary::BeginRecordFullViewport( WorldContextObject,  InGeneratedWebpPicturesPath);
}

void UXGWebpBPLibrary::EndRecord(UObject* WorldContextObject, FXGWebpFinishGenerateWebp InFinishWebpBPDegelete)
{
	UXGWebpLibrary::EndRecord(WorldContextObject,FSimpleDelegate(), InFinishWebpBPDegelete);
}

