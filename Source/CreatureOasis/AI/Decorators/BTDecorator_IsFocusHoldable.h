// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsFocusHoldable.generated.h"

/**
 * Returns true if Focus Actor is in Holdable range, Agent Avatar must needs to have UHoldableAnchorComponent
 */
UCLASS()
class CREATUREOASIS_API UBTDecorator_IsFocusHoldable : public UBTDecorator
{
	GENERATED_BODY()
	
	UBTDecorator_IsFocusHoldable();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
