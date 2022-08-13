// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"

#include "BTService_SelectStatBasedCreatureAction.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UBTService_SelectStatBasedCreatureAction : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_SelectStatBasedCreatureAction();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
protected:
	UPROPERTY(EditAnywhere, Category=GameplayTagCheck,
		Meta=(ToolTips="Which bool (from the blackboard) should be used to communicate to the BT that an action was succesfully selected?"))
	FBlackboardKeySelector BooleanBKeyToSet;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MovementModeTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer HasTheseStatActionTags;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer IgnoreTheseStatActionTags;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag DynamicBTInjectionTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBehaviorTree* DefaultBTToRun;
};
