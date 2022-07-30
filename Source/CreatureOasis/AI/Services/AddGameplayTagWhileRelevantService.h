// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "AddGameplayTagWhileRelevantService.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UAddGameplayTagWhileRelevantService : public UBTService
{
	GENERATED_BODY()

public:
	UAddGameplayTagWhileRelevantService();
	
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer GameplayTagsToAdd;
};
