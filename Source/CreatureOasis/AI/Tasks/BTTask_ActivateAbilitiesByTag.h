// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ActivateAbilitiesByTag.generated.h"

/**
 * Activates one or multiple abilities that the owning pawn with a Gameplay Ability Component has equipped
 * If none are found this task will fail
 */
UCLASS()
class CREATUREOASIS_API UBTTask_ActivateAbilitiesByTag : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ActivateAbilitiesByTag();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag GameplayTag;

	// If true, this task will activate the ability and instantly finish
	UPROPERTY(EditAnywhere)
	bool bNonBlocking;
};
