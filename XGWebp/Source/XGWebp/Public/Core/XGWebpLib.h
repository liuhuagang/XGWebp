// Copyright Xiao Gang. All Rights Reserved.
#pragma once

#include "vector"
#include "XGWebpCore.h"

/**
 * if you are not good at c/c++,you had better not use this class, in case of memory leak
 * if you really want to use this , you should change the source code of the class. such as delete "protected".....
 * if you want to do more about webp,you can read XGWebp/XGWebpLibrary/*.h,which contain anything you can with webp
 */
struct FXGWebpLibStruct
{
	friend class FXGWebpCore;
protected:

	static bool GenerateWebpByRGBA(
		const char* InWebpSavePath,
		const unsigned char* InRGBAData,
		int                  InWidth,
		int                  InHeight,
		float                InQualityFactor = 100);

	static bool GenerateDymaicWebpByRGBA(
		const char* InWebpSavePath,
		std::vector<const unsigned char*>& InRGBADatas,
		std::vector<int>                   InTimestamps_ms,
		int                                InWidth,
		int                                InHeight,
		float                              InQualityFactor = 100);

	static bool LoadDynamicWebpPictureByRGBA(
		const char* InWebpFilePath,
		std::vector<const unsigned char*>& OutRGBADatas,
		std::vector<int>&                  OutTimestamps_ms,
		int&                                OutWidth,
		int&                                OutHeight);



	static bool ResizeDynamicWebp(
		const char* InResizedWebpPath,
		const char* InWebpSavePath,
		int         InResizeWidth,
		int         InResizeHight,
		int         InQualityFactor = 100);



};

