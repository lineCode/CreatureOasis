// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ApplyGameplayEffectWhileRelevant.h"

#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AIController.h"

UBTService_ApplyGameplayEffectWhileRelevant::UBTService_ApplyGameplayEffectWhileRelevant()
	: bDoNotRemoveOnCeaseRelevant(false)
{
	NodeName = "Apply GameplayEffect while relevant";

	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}

void UBTService_ApplyGameplayEffectWhileRelevant::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	const AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn();
	if (OwnerActor->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OwnerActor);
		UAbilitySystemComponent* ASC = AbilitySystemInterface->GetAbilitySystemComponent();

		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		
		const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GameplayEffectToApply, 1, EffectContext);
		if (SpecHandle.IsValid())
		{
			ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void UBTService_ApplyGameplayEffectWhileRelevant::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);

	if (bDoNotRemoveOnCeaseRelevant)
	{
		return;
	}
	
	const AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn();
	if (IsValid(OwnerActor) && OwnerActor->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OwnerActor);
		UAbilitySystemComponent* ASC = AbilitySystemInterface->GetAbilitySystemComponent();
		
		ASC->RemoveActiveGameplayEffectBySourceEffect(GameplayEffectToApply, nullptr);
	}
}
