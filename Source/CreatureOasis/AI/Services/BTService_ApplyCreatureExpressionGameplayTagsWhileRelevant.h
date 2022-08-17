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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditConditionHides = "!bUseContainer || bClearEyesOnEmptyTag"))
	FGameplayTag EyeTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditConditionHides = "!bUseContainer || bClearMouthOnEmptyTag"))
	FGameplayTag MouthTag;

	// Allows for defining a container of tags in use for selecting a random tag
	UPROPERTY(EditAnywhere)
	bool bUseContainer;

	UPROPERTY(EditAnywhere, meta = (EditConditionHides = "bUseContainer || bClearEyesOnEmptyTag"))
	FGameplayTagContainer EyeTagContainer;

	UPROPERTY(EditAnywhere, meta = (EditConditionHides = "bUseContainer || bClearMouthOnEmptyTag"))
	FGameplayTagContainer MouthTagContainer;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bDoNotRemoveOnCeaseRelevant;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bClearEyesOnEmptyTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bClearMouthOnEmptyTag;
};
