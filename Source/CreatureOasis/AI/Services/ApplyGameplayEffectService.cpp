// Fill out your copyright notice in the Description page of Project Settings.


#include "ApplyGameplayEffectService.h"

#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

UApplyGameplayEffectService::UApplyGameplayEffectService()
	: bRemoveOnCeaseRelevant(true)
{
	NodeName = "Apply GameplayEffect";

	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}

void UApplyGameplayEffectService::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	const AActor* OwnerActor = OwnerComp.GetOwner();
	if (OwnerActor->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OwnerActor);
		AbilitySystemInterface->GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(GameplayEffectToApply, 0.f, FGameplayEffectContextHandle());
	}
}

void UApplyGameplayEffectService::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);

	if (!bRemoveOnCeaseRelevant)
	{
		return;
	}
	
	const AActor* OwnerActor = OwnerComp.GetOwner();
	if (OwnerActor->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OwnerActor);
		UAbilitySystemComponent* ASC = AbilitySystemInterface->GetAbilitySystemComponent();
		ASC->RemoveActiveGameplayEffectBySourceEffect(GameplayEffectToApply->StaticClass(), nullptr);
	}
}
