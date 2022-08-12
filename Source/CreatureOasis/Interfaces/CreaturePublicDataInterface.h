// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CreatureOasis/Structs/CreatureDataLoad.h"
#include "UObject/Interface.h"

#include "CreaturePublicDataInterface.generated.h"

UINTERFACE()
class UCreaturePublicDataInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CREATUREOASIS_API ICreaturePublicDataInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="CreaturePublicData")
	FString GetCreatureName();
};
