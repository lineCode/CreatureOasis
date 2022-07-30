// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"

#include "CreatureStatWidgetInterface.generated.h"

UINTERFACE()
class UCreatureStatWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CREATUREOASIS_API ICreatureStatWidgetInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="HUDCreatureStatDisplayInterface")
	void SetTargetActor(AActor* NewTargetActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="HUDCreatureStatDisplayInterface")
	void SetWidgetVisibility(bool bIsVisible);
};
