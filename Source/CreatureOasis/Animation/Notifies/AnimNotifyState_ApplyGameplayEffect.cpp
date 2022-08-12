// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_ApplyGameplayEffect.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

void UAnimNotifyState_ApplyGameplayEffect::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                       float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	const AActor* OwnerActor = MeshComp->GetOwner();
	if (IsValid(OwnerActor) && OwnerActor->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
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

void UAnimNotifyState_ApplyGameplayEffect::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	const AActor* OwnerActor = MeshComp->GetOwner();
	if (IsValid(OwnerActor) && OwnerActor->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OwnerActor);
		UAbilitySystemComponent* ASC = AbilitySystemInterface->GetAbilitySystemComponent();
		
		ASC->RemoveActiveGameplayEffectBySourceEffect(GameplayEffectToApply, nullptr);
	}
}
