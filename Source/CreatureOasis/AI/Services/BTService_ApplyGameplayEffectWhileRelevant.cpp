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

	ApplyDelayWaitTime = 0.f;
	
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
	bNotifyTick = false;
}

void UBTService_ApplyGameplayEffectWhileRelevant::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	const AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn();
	if (OwnerActor->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OwnerActor);
		UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();

		if (ApplyDelayWaitTime > 0.f)
		{
			FBTApplyGameplayEffectWhileRelevantMemory* MyMemory = CastInstanceNodeMemory<FBTApplyGameplayEffectWhileRelevantMemory>(NodeMemory);
			MyMemory->RemainingWaitTime = FMath::FRandRange(FMath::Max(0.0f, ApplyDelayWaitTime - ApplyDelayWaitTimeRandomDeviation), (ApplyDelayWaitTime + ApplyDelayWaitTimeRandomDeviation));
			bNotifyTick = true;
		}
		else
		{
			ApplyGameplayEffect(AbilitySystemComponent);
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

void UBTService_ApplyGameplayEffectWhileRelevant::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	FBTApplyGameplayEffectWhileRelevantMemory* MyMemory = CastInstanceNodeMemory<FBTApplyGameplayEffectWhileRelevantMemory>(NodeMemory);
	MyMemory->RemainingWaitTime -= DeltaSeconds;
	
	if (MyMemory->RemainingWaitTime <= 0.f)
	{
		bNotifyTick = false;

		const AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn();
		if (IsValid(OwnerActor) && OwnerActor->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
		{
			const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OwnerActor);
			UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();
			ApplyGameplayEffect(AbilitySystemComponent);
		}
	}
}

uint16 UBTService_ApplyGameplayEffectWhileRelevant::GetInstanceMemorySize() const
{
	return sizeof(FBTApplyGameplayEffectWhileRelevantMemory);
}

void UBTService_ApplyGameplayEffectWhileRelevant::ApplyGameplayEffect(UAbilitySystemComponent* AbilitySystemComponent) const
{
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);
		
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectToApply, 1, EffectContext);
	if (SpecHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}
