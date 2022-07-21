﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GardenStaticsBlueprintLibrary.generated.h"

class UGardenActorsManager;
class ABaseGardenGameMode;
class ABaseGardenGameMode;

/**
 * Static class with useful utility functions for the garden mode that can be called from both Blueprint and C++
 */
UCLASS()
class CREATUREOASIS_API UGardenStaticsBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Gets current GameMode cast to BaseGardenGameMode
	 * @return current GameMode of type BaseGardenGameMode, nullptr if failed
	 * @note Only intended for Garden modes
	 */
	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext), Category="GardenStatics")
	static ABaseGardenGameMode* GetGardenGameMode(const UObject* WorldContextObject);
};