// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FuzzyLogicInterface.generated.h"

/**
 * 
 */
UINTERFACE(Blueprintable)
class CREATUREOASIS_API UFuzzyLogicInterface : public UInterface
{
	GENERATED_BODY()
};

class IFuzzyLogicInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float CalculateScore();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	class UBehaviorTree* GetBehaviorTreeToRun();
};