// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CreatureMoveTo.h"

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "CreatureOasis/Creature/CreatureAIController.h"

UBTTask_CreatureMoveTo::UBTTask_CreatureMoveTo()
{
	NodeName = TEXT("Creature Rotate and Move To");

	AcceptableRadius = 30.f;
	
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_CreatureMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIController = Cast<ACreatureAIController>(OwnerComp.GetAIOwner());
	
	TargetLocation = AIController->GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
	
	return EBTNodeResult::InProgress;
}

void UBTTask_CreatureMoveTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	AIController->RotateGraduallyTowardsTarget(TargetLocation);
	AIController->MoveForward();
	
	// Acceptable radius
	if (AIController->IsCreatureAtLocation(TargetLocation, AcceptableRadius))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	// Draw sphere at target location
	DrawDebugSphere(GetWorld(), TargetLocation + FVector(0.f, 0.f, 4.f), AcceptableRadius, 8, FColor::Magenta);
}
