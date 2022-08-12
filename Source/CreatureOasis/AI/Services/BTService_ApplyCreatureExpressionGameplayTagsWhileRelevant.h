// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_ApplyCreatureExpressionGameplayTagsWhileRelevant.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UBTService_ApplyCreatureExpressionGameplayTagsWhileRelevant : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_ApplyCreatureExpressionGameplayTagsWhileRelevant();
	
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag EyeTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MouthTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bDoNotRemoveOnCeaseRelevant;
};
