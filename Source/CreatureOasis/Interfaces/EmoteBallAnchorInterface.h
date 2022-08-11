// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"

#include "EmoteBallAnchorInterface.generated.h"

UINTERFACE()
class UEmoteBallAnchorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CREATUREOASIS_API IEmoteBallAnchorInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="EmoteBallAnchorInterface")
	USceneComponent* GetEmoteBallAnchorComponent();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="EmoteBallAnchorInterface")
    USceneComponent* GetEmoteBallBaseComponent();
};
