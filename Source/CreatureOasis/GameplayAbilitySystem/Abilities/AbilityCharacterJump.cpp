// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityCharacterJump.h"

#include "CreatureOasis/GameplayAbilitySystem/GASCharacter.h"
#include "GameFramework/Character.h"

UAbilityCharacterJump::UAbilityCharacterJump()
{
	AbilityInputID = EAbilityInputID::Jump;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Jump")));
}

void UAbilityCharacterJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}

	ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());
	Character->Jump();
}

bool UAbilityCharacterJump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	const AGASCharacter* Character = CastChecked<AGASCharacter>(ActorInfo->AvatarActor.Get(), ECastCheckedType::NullAllowed);
	return Character && Character->CanJump();
}

void UAbilityCharacterJump::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (ActorInfo != nullptr && ActorInfo->AvatarActor != nullptr)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}
}

void UAbilityCharacterJump::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());
	Character->StopJumping();
}
