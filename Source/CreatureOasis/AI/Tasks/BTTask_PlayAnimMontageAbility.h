// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UObject/Object.h"
#include "BTTask_PlayAnimMontageAbility.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UBTTask_PlayAnimMontageAbility : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_PlayAnimMontageAbility();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag StartEventGameplayTag;

	UPROPERTY(EditAnywhere)
	FGameplayTag EndEventGameplayTag;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* AnimMontageToPlay;

	UPROPERTY(EditAnywhere)
	TArray<FName> MontageSectionStrings;

	UPROPERTY(EditAnywhere)
	float MinWait;

	UPROPERTY(EditAnywhere)
	float MaxWait;
};
