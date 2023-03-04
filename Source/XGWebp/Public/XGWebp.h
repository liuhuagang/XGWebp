// Copyright 2023 XiaoGang 

#pragma once

#include "Modules/ModuleManager.h"

class FXGWebpModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

};
