// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CreatureMoveTo.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTask_CreatureMoveTo::UBTTask_CreatureMoveTo()
{
	NodeName = TEXT("Creature Move To");
}

EBTNodeResult::Type UBTTask_CreatureMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const AIController = OwnerComp.GetAIOwner();
	const FVector TargetLocation = AIController->GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
	
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(AIController, TargetLocation);
	
	return EBTNodeResult::Succeeded;
}
