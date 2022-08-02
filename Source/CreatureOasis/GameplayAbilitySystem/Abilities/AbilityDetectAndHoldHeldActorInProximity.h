// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureOasis/GameplayAbilitySystem/BaseGameplayAbility.h"
#include "AbilityDetectAndHoldHeldActorInProximity.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UAbilityDetectAndHoldHeldActorInProximity : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	UAbilityDetectAndHoldHeldActorInProximity();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
};
