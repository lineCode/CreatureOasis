// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "UObject/Object.h"
#include "BTDecorator_RandomChance.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UBTDecorator_RandomChance : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_RandomChance();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	// 0.f = 0% chance | 0.5 = 50% chance | 1.f = 100% chance
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 0.f, ClampMax = 1.f))
	float RandomChance;
};
