﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureOasis/AI/FuzzyLogic/FuzzyLogicInterface.h"
#include "BaseDynamicBTAction.generated.h"

class UGardenActorsSubsystem;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class CREATUREOASIS_API UBaseDynamicBTAction : public UObject, public IFuzzyLogicInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BehaviorTreeToRun;

	// IFuzzyLogicInterface implementations
	virtual float CalculateScore_Implementation(UWorld* World, AAIController* AIController, const class UBaseAbilitySystemComponent* BaseAbilitySystemComponent) override;
	virtual UBehaviorTree* GetBehaviorTreeToRun_Implementation() override;

protected:
	UFUNCTION(BlueprintCallable)
	UGardenActorsSubsystem* GetGardenActorsSubsystem(const UWorld* World) const;
};
