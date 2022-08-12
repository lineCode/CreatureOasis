// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CreatureOasis/Structs/CreatureDataLoad.h"
#include "UObject/Interface.h"

#include "CreatureComponentLoadableInterface.generated.h"

UINTERFACE()
class UCreatureComponentLoadableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CREATUREOASIS_API ICreatureComponentLoadableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="CreatureDataLoad")
	void LoadCreatureData(const FCreatureDataLoad& CreatureDataLoad);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="CreatureDataLoad")
	void GatherCreatureData(FCreatureDataLoad& CreatureDataLoad);
};
