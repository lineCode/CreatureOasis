// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ActivateAbilitiesByTag.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayTag.h"
#include "CreatureOasis/GameplayAbilitySystem/GASPawn.h"

UBTTask_ActivateAbilitiesByTag::UBTTask_ActivateAbilitiesByTag() :
	bNonBlocking(false)
{
	NodeName = "Activate Abilities By Tag";
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
		AbilitySystemComponent->RegisterGameplayTagEvent(GameplayTag, EGameplayTagEventType::NewOrRemoved)
			.AddLambda([&](const FGameplayTag CallbackTag, int32 NewCount)
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			});
	}
	else
	{
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::InProgress;
}