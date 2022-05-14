// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CreatureRotateAndMoveTo.h"

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "CreatureOasis/Characters/Creature/CreatureAIController.h"

UBTTask_CreatureRotateAndMoveTo::UBTTask_CreatureRotateAndMoveTo()
{
	NodeName = TEXT("Creature Rotate and Move To");

	AcceptableRadius = 30.f;
	
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_CreatureRotateAndMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}

void UBTTask_CreatureRotateAndMoveTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	const FVector TargetLocation = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
	const ACreatureAIController* AIController = Cast<ACreatureAIController>(OwnerComp.GetAIOwner());
	
	AIController->RotateGraduallyTowardsTarget(TargetLocation);
	AIController->MoveForward();
	
	// Acceptable radius
	if (AIController->IsAtLocation(TargetLocation, AcceptableRadius))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	// Draw sphere at target location
	DrawDebugSphere(GetWorld(), TargetLocation + FVector(0.f, 0.f, 4.f), AcceptableRadius, 8, FColor::Magenta);
}
