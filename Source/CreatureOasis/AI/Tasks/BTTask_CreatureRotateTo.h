// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_CreatureRotateTo.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UBTTask_CreatureRotateTo : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_CreatureRotateTo();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Tolerance;
};
