// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_EndAbilitiesByTag.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AIController.h"

UBTTask_EndAbilitiesByTag::UBTTask_EndAbilitiesByTag()
	: bNonBlocking(false)
{
	NodeName = "End Abilities By Tag";
}

EBTNodeResult::Type UBTTask_EndAbilitiesByTag::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	if (AbilitySystemComponent->HasMatchingGameplayTag(GameplayTag))
	{
		const FGameplayTagContainer TagContainer = FGameplayTagContainer(GameplayTag);
		AbilitySystemComponent->CancelAbilities(&TagContainer);
	
		if (bNonBlocking)
		{
			return EBTNodeResult::Succeeded;
		}
		
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
