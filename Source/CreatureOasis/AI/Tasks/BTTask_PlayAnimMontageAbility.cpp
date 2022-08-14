// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PlayAnimMontageAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AIController.h"
#include "CreatureOasis/Objects/PlayMontageGameplayEventObject.h"

UBTTask_PlayAnimMontageAbility::UBTTask_PlayAnimMontageAbility()
	: StartEventGameplayTag(FGameplayTag::RequestGameplayTag("Event.Chao.PlayMontage"))
	, EndEventGameplayTag(FGameplayTag::RequestGameplayTag("Event.Chao.EndMontage"))
{
	NodeName = "PlayAnimMontageAbility";

	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_PlayAnimMontageAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();

	if (!IsValid(AIController) || !IsValid(AIController->GetPawn()) || !StartEventGameplayTag.IsValid())
	{
		return EBTNodeResult::Failed;
	}
	
	const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(AIController->GetPawn());

	if (!AbilitySystemInterface)
	{
		return EBTNodeResult::Failed;
	}
	
	UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();

	UPlayMontageGameplayEventObject* EventObject = NewObject<UPlayMontageGameplayEventObject>();
	EventObject->InitializeWithData(AnimMontageToPlay, MontageSectionStrings, MinWait, MaxWait, &OwnerComp, this);
	
	FGameplayEventData GameplayEventData;
	GameplayEventData.OptionalObject = EventObject;
	
	AbilitySystemComponent->HandleGameplayEvent(StartEventGameplayTag, &GameplayEventData);
	
	return EBTNodeResult::InProgress;
}

void UBTTask_PlayAnimMontageAbility::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();

	if (!IsValid(AIController) || !IsValid(AIController->GetPawn()) || !EndEventGameplayTag.IsValid())
	{
		return;
	}
	
	const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(AIController->GetPawn());
	UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();

	switch (TaskResult) {
		case EBTNodeResult::Failed:
		case EBTNodeResult::Aborted:
			{
				const FGameplayEventData EventData;
				AbilitySystemComponent->HandleGameplayEvent(EndEventGameplayTag, &EventData);
			}
		default: ;
	}
}
