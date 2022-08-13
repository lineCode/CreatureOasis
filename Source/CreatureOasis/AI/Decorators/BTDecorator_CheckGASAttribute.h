// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "BehaviorTree/BTDecorator.h"
#include "CreatureOasis/CreatureOasis.h"
#include "BTDecorator_CheckGASAttribute.generated.h"

/**
 * Use this Decorator node to check a GAS Attribute
 */
UCLASS()
class CREATUREOASIS_API UBTDecorator_CheckGASAttribute : public UBTDecorator
{
	GENERATED_BODY()

	UBTDecorator_CheckGASAttribute();
	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	bool CommenceComparativeCheck(const float ValToCheck) const;

	UPROPERTY(EditAnywhere)
	FScalableFloat ScalableFloat;
	
	UPROPERTY(EditAnywhere)
	ECheckCompareQuery CheckQuery;
	
	UPROPERTY(EditAnywhere)
	FGameplayAttribute TargetAttribute;
};
