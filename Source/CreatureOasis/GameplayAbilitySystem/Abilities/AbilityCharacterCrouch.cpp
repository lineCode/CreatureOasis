// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityCharacterCrouch.h"

#include "GameFramework/Character.h"

UAbilityCharacterCrouch::UAbilityCharacterCrouch()
{
	AbilityInputID = EAbilityInputID::Crouch;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Crouch")));
}

void UAbilityCharacterCrouch::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
	
	ActorInfo->PlayerController->GetCharacter()->Crouch();
}

bool UAbilityCharacterCrouch::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	const ACharacter* Character = ActorInfo->PlayerController->GetCharacter();
	return Character && Character->CanCrouch();
}

void UAbilityCharacterCrouch::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (ActorInfo != nullptr && ActorInfo->AvatarActor != nullptr)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}
}

void UAbilityCharacterCrouch::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	ActorInfo->PlayerController->GetCharacter()->UnCrouch();
}
