// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityDetectAndHoldHeldActorInProximity.h"

UAbilityDetectAndHoldHeldActorInProximity::UAbilityDetectAndHoldHeldActorInProximity()
{
	
}

void UAbilityDetectAndHoldHeldActorInProximity::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAbilityDetectAndHoldHeldActorInProximity::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}
