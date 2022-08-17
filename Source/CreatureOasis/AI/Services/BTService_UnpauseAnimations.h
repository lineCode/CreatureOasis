// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UnpauseAnimations.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UBTService_UnpauseAnimations : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_UnpauseAnimations();
	
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
