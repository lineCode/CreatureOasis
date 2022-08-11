// Fill out your copyright notice in the Description page of Project Settings.


#include "AddGameplayTagWhileRelevantService.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AIController.h"
#include "CreatureOasis/GameplayAbilitySystem/GASCharacter.h"

UAddGameplayTagWhileRelevantService::UAddGameplayTagWhileRelevantService()
{
	NodeName = "Set gameplay tag while relevant";

	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}

void UAddGameplayTagWhileRelevantService::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	const AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn();
	if (OwnerActor->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		const AGASCharacter* GASCharacter = Cast<AGASCharacter>(OwnerActor);
		GASCharacter->GetAbilitySystemComponent()->AddLooseGameplayTags(GameplayTagsToAdd);
	}
}

void UAddGameplayTagWhileRelevantService::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);

	const AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn();
	if (IsValid(OwnerActor) && OwnerActor->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		const AGASCharacter* GASCharacter = Cast<AGASCharacter>(OwnerActor);
		GASCharacter->GetAbilitySystemComponent()->RemoveLooseGameplayTags(GameplayTagsToAdd);
	}
}
