// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "UObject/Object.h"
#include "BTService_RemoveGameplayEffect.generated.h"

class UGameplayEffect;

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UBTService_RemoveGameplayEffect : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_RemoveGameplayEffect();
	
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> GameplayEffectToRemove;

};
