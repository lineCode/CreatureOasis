// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_EndAbilitiesByTag.generated.h"

/**
 * Ends one or multiple abilities that the owning pawn with a Gameplay Ability Component has equipped
 * If none are found this task will fail
 */
UCLASS()
class CREATUREOASIS_API UBTTask_EndAbilitiesByTag : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_EndAbilitiesByTag();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag GameplayTag;

	// If true, this task will end the ability and instantly finish
	UPROPERTY(EditAnywhere)
	bool bNonBlocking;
};
