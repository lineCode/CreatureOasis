#pragma once

#include "CoreMinimal.h"
#include "CreatureOasis/GameplayAbilitySystem/BaseGameplayAbility.h"
#include "AbilityCharacterHoldActor.generated.h"

/**
 * Makes the Character attempt to pick up, hold and release an Actor
 */
UCLASS()
class CREATUREOASIS_API UAbilityCharacterHoldActor : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	UAbilityCharacterHoldActor();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	
protected:
	float PickUpSphereRadius;
};
