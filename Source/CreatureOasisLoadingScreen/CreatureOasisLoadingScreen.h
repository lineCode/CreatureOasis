﻿#pragma once

#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

// Based on the ActionRPG loading screen
class FCreatureOasisLoadingScreen : public IModuleInterface
{
public:
	/* Loads the module so it can be turned on */
	static inline FCreatureOasisLoadingScreen& Get()
	{
		return FModuleManager::LoadModuleChecked<FCreatureOasisLoadingScreen>("Zephyr_DemoLoadingScreen");
	}
	
	// Start IModuleInterface
	virtual void StartupModule() override;
	virtual bool IsGameModule() const override;
	// End

	virtual void StartInGameLoadingScreen(bool bPlayUntilStopped, float PlayTime);
	virtual void StopInGameLoadingScreen();
	
	virtual void CreateScreen();
};