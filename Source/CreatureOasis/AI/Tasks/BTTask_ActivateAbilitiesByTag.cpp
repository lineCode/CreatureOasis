// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ActivateAbilitiesByTag.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayTag.h"
#include "CreatureOasis/GameplayAbilitySystem/GASPawn.h"

UBTTask_ActivateAbilitiesByTag::UBTTask_ActivateAbilitiesByTag()
	: bNonBlocking(false)
{
	NodeName = "Activate Abilities By Tag";

	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_ActivateAbilitiesByTag::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();

	if (!IsValid(AIController) || !IsValid(AIController->GetPawn()) || !GameplayTag.IsValid())
	{
		return EBTNodeResult::Failed;
	}
	
	const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(AIController->GetPawn());

	if (!AbilitySystemInterface)
	{
		return EBTNodeResult::Failed;
	}
	
	UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();

	if(!AbilitySystemComponent->TryActivateAbilitiesByTag(FGameplayTagContainer(GameplayTag)))
	{
		return EBTNodeResult::Failed;
	}
	
	if (bNonBlocking)
	{
		return EBTNodeResult::Succeeded;
	}

	if (AbilitySystemComponent->HasMatchingGameplayTag(GameplayTag))
	{
		FDelegateHandle DelegateHandle = AbilitySystemComponent->RegisterGameplayTagEvent(GameplayTag, EGameplayTagEventType::NewOrRemoved)
			.AddLambda([&](const FGameplayTag CallbackTag, int32 NewCount)
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			});
		
		DelegateMap.Add(TTuple<FGameplayTag, FDelegateHandle>(GameplayTag,DelegateHandle));
	}
	else
	{
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::InProgress;
}

void UBTTask_ActivateAbilitiesByTag::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OwnerComp.GetAIOwner()->GetPawn());
	UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();

	AbilitySystemComponent->UnregisterGameplayTagEvent(DelegateMap.FindRef(GameplayTag), GameplayTag, EGameplayTagEventType::NewOrRemoved);
}
