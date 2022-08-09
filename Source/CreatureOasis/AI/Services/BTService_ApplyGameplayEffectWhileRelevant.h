// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "BehaviorTree/BTService.h"
#include "BTService_ApplyGameplayEffectWhileRelevant.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UBTService_ApplyGameplayEffectWhileRelevant : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_ApplyGameplayEffectWhileRelevant();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> GameplayEffectToApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bDoNotRemoveOnCeaseRelevant;
};
