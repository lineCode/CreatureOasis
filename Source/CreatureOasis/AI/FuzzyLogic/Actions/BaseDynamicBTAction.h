// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureOasis/AI/FuzzyLogic/FuzzyLogicInterface.h"
#include "BaseDynamicBTAction.generated.h"

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
	virtual float CalculateScore_Implementation() override;
	virtual UBehaviorTree* GetBehaviorTreeToRun_Implementation() override;
};
