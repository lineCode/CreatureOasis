// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_EndAbilitiesByTag.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AIController.h"

UBTTask_EndAbilitiesByTag::UBTTask_EndAbilitiesByTag()
	: bNonBlocking(false)
{
	NodeName = "End Abilities By Tag";

	bNotifyTaskFinished = true;
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

void UBTTask_EndAbilitiesByTag::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OwnerComp.GetAIOwner()->GetPawn());
	UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();

	AbilitySystemComponent->UnregisterGameplayTagEvent(DelegateMap.FindRef(GameplayTag), GameplayTag, EGameplayTagEventType::NewOrRemoved);
}
