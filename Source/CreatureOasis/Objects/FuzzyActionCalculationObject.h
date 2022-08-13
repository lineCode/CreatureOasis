// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CreatureOasis/Interfaces/FuzzyLogicInterface.h"
#include "FuzzyActionCalculationObject.generated.h"

class UAbilitySystemComponent;
class UGardenActorsSubsystem;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class CREATUREOASIS_API UFuzzyActionCalculationObject : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float CalculateScore(UWorld* World, AAIController* AIController,
	                     const UAbilitySystemComponent* BaseAbilitySystemComponent);
	
protected:
	UFUNCTION(BlueprintCallable)
	UGardenActorsSubsystem* GetGardenActorsSubsystem(const UWorld* World) const;
};
