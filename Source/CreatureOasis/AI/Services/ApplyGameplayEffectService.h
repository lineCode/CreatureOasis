// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ApplyGameplayEffectService.generated.h"

class UGameplayEffect;

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UApplyGameplayEffectService : public UBTService
{
	GENERATED_BODY()

public:
	UApplyGameplayEffectService();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UGameplayEffect* GameplayEffectToApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bRemoveOnCeaseRelevant;
};
