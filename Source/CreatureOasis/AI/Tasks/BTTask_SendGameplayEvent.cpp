// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SendGameplayEvent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SendGameplayEvent::UBTTask_SendGameplayEvent()
{
	BlackboardKey.AddClassFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_SendGameplayEvent, BlackboardKey), TSubclassOf<AActor>());
}

EBTNodeResult::Type UBTTask_SendGameplayEvent::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* TargetActor = Cast<AActor>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(TargetActor, EventTag, FGameplayEventData());
	
	return EBTNodeResult::Succeeded;
}
