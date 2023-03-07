// Copyright Xiao Gang. All Rights Reserved.
#pragma once

#include "vector"
#include "XGWebpCore.h"



struct FXGWebpLibStruct
{
	friend class FXGWebpCore;
protected:

	static bool GenerateWebpByRGBA(const char* InWebpSavePath,
		const unsigned char* InRGBAData,
		int                  InWidth,
		int                  InHeight,
		float                InQualityFactor = 100);

	static bool GenerateDymaicWebpByRGBA(const char* InWebpSavePath,
		std::vector<const unsigned char*>& InRGBADatas,
		std::vector<int>                   InTimestamps_ms,
		int                                InWidth,
		int                                InHeight,
		float                              InQualityFactor = 100);

	static bool ResizeDynamicWebp(const char* InResizedWebpPath,
		const char* InWebpSavePath,
		int         InResizeWidth,
		int         InResizeHight,
		int         InQualityFactor = 100);
};

