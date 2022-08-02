// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityCharacterHoldActor.h"

#include "AbilitySystemComponent.h"
#include "CreatureOasis/Components/HoldableAnchorComponent.h"
#include "CreatureOasis/GameplayAbilitySystem/GASCharacter.h"
#include "CreatureOasis/Interfaces/HoldableInterface.h"
#include "GameFramework/Character.h"

UAbilityCharacterHoldActor::UAbilityCharacterHoldActor()
	: ActiveGameplayTag(FGameplayTag::RequestGameplayTag(FName("Ability.HoldActor")))
{
	AbilityInputID = EAbilityInputID::Interact;
	
	AbilityTags.AddTag(ActiveGameplayTag);
	ActivationOwnedTags.AddTag(ActiveGameplayTag);
}

void UAbilityCharacterHoldActor::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
    	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
    }

	AGASCharacter* Character = CastChecked<AGASCharacter>(ActorInfo->AvatarActor.Get());
	
	UHoldableAnchorComponent* HoldableAnchorComponent = Character->FindComponentByClass<UHoldableAnchorComponent>();
	if (IsValid(HoldableAnchorComponent))
	{
		AActor* ActorToHold = HoldableAnchorComponent->DetectHoldableActor();
		if (IsValid(ActorToHold))
		{
			// Make sure that when the ActorToHold is already being held by a GASCharacter we Detach from it first 
			const AGASCharacter* HolderOfActorToHold = IHoldableInterface::Execute_GetCharacterCurrentlyHoldingUs(ActorToHold);
			if (IsValid(HolderOfActorToHold))
			{
				HolderOfActorToHold->GetAbilitySystemComponent()->CancelAllAbilities();
			}
			
			IHoldableInterface::Execute_StartBeingHold(ActorToHold, Character);
		
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