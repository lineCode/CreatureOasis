// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_CreatureRotateAndMoveTo.generated.h"

/**
 * Rotates and moves towards a specific Actor or Location
 * Will continue onwards until in an AcceptableRadius
 */
UCLASS()
class CREATUREOASIS_API UBTTask_CreatureRotateAndMoveTo : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_CreatureRotateAndMoveTo();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition="!bIgnoreAcceptableRadius"))
	float AcceptableRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition="!bOnlySetFocalPoint"))
	bool bOnlyMoveForwards;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition="!bOnlyMoveForwards"))
	bool bOnlySetFocalPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIgnoreAcceptableRadius;
};