// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityCharacterHoldActor.h"

#include "CreatureOasis/Components/HoldableAnchorComponent.h"
#include "CreatureOasis/Interfaces/HoldableInterface.h"
#include "GameFramework/Character.h"

UAbilityCharacterHoldActor::UAbilityCharacterHoldActor()
{
	AbilityInputID = EAbilityInputID::Interact;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.HoldActor")));
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.HoldActor")));
}

void UAbilityCharacterHoldActor::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
    	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
    }

	const ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());
	
	UHoldableAnchorComponent* HoldableAnchorComponent = Character->FindComponentByClass<UHoldableAnchorComponent>();
	if (IsValid(HoldableAnchorComponent))
	{
		AActor* ActorToHold = HoldableAnchorComponent->DetectHoldableActor();
		if(IsValid(ActorToHold))
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow,
											 FString::Printf(TEXT("Holding %s"), *ActorToHold->GetName()));
		
			IHoldableInterface::Execute_StartBeingHold(ActorToHold, ActorInfo->AvatarActor.Get());
		
			HoldableAnchorComponent->AttachHoldable(ActorToHold);
		}
	}
}

bool UAbilityCharacterHoldActor::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UAbilityCharacterHoldActor::CancelAbility(const FGameplayAbilitySpecHandle Handle,
                                               const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                               bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	UHoldableAnchorComponent* HoldableAnchorComponent = ActorInfo->AvatarActor->FindComponentByClass<UHoldableAnchorComponent>();
	
	if (HoldableAnchorComponent != nullptr)
	{
		AActor* ActorWeAreHolding = HoldableAnchorComponent->GetActorWeAreHolding();
		if (IsValid(ActorWeAreHolding))
		{
			IHoldableInterface::Execute_EndBeingHold(ActorWeAreHolding);
		}

		HoldableAnchorComponent->DetachHoldable();
	}
}

void UAbilityCharacterHoldActor::InputPressed(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (ActorInfo != nullptr && ActorInfo->AvatarActor != nullptr)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}
}