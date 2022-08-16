// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CreatureRotateTo.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "CreatureOasis/Characters/Creature/CreatureAIController.h"
#include "GameFramework/Character.h"

UBTTask_CreatureRotateTo::UBTTask_CreatureRotateTo()
{
	NodeName = TEXT("Check if Rotation is met");

	Tolerance = 4.0f;

	bNotifyTick = true;

	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_CreatureRotateTo, BlackboardKey));
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_CreatureRotateTo, BlackboardKey), AActor::StaticClass());
}

EBTNodeResult::Type UBTTask_CreatureRotateTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}

void UBTTask_CreatureRotateTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	FVector TargetLoc;
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		const UObject* GotObject = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey());
		if (!IsValid(GotObject))
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return;
		}

		const AActor* Actor = Cast<AActor>(GotObject);
		if (!IsValid(Actor))
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return;
		}
		
		TargetLoc = Actor->GetActorLocation();
	}
	else
	{
		TargetLoc = OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
	}

	const FVector TargetDirection = (TargetLoc - OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation());
	if (FMath::Abs( OwnerComp.GetAIOwner()->GetPawn()->GetActorRotation().Yaw - TargetDirection.Rotation().Yaw) <= Tolerance)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
