// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CreatureOasis/Components/CreatureExpressionComponent.h"
#include "CreatureOasis/Structs/CreatureDataLoad.h"
#include "UObject/Interface.h"

#include "CreatureComponentGetterInterface.generated.h"

UINTERFACE()
class UCreatureComponentGetterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CREATUREOASIS_API ICreatureComponentGetterInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="CreatureComponentGetterInterface")
	UCreatureExpressionComponent* GetCreatureExpressionComponent();
};
