// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_RemoveGameplayEffect.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AIController.h"

UBTService_RemoveGameplayEffect::UBTService_RemoveGameplayEffect()
{
	NodeName = "RemoveGameplayEffect";
	
	bNotifyBecomeRelevant = true;
	bNotifyTick = false;
}

void UBTService_RemoveGameplayEffect::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	const AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn();
	if (OwnerActor->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OwnerActor);
		UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();

		AbilitySystemComponent->RemoveActiveGameplayEffectBySourceEffect(GameplayEffectToRemove, nullptr);
	}
}
