// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "BehaviorTree/BTService.h"
#include "BTService_ApplyGameplayEffectWhileRelevant.generated.h"

struct FBTApplyGameplayEffectWhileRelevantMemory
{
	float RemainingWaitTime;
};

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
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	virtual uint16 GetInstanceMemorySize() const override;
	
	void ApplyGameplayEffect(UAbilitySystemComponent* AbilitySystemComponent) const;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> GameplayEffectToApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bDoNotRemoveOnCeaseRelevant;

	// If set we wait a set amount of time before we apply the gameplay effect
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ApplyDelayWaitTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ApplyDelayWaitTimeRandomDeviation;
};