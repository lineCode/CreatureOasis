// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CreatureRotateTo.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "CreatureOasis/Creature/CreatureAIController.h"

UBTTask_CreatureRotateTo::UBTTask_CreatureRotateTo()
{
	NodeName = TEXT("Creature Rotate To");

	Tolerance = 0.0f;
	
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_CreatureRotateTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}

void UBTTask_CreatureRotateTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	const ACreatureAIController* AIController = Cast<ACreatureAIController>(OwnerComp.GetAIOwner());
	const FVector TargetLocation = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());;
	
	AIController->RotateGraduallyTowardsTarget(TargetLocation);
	
	if (AIController->IsRotatedTowardsLocation(TargetLocation, Tolerance))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
