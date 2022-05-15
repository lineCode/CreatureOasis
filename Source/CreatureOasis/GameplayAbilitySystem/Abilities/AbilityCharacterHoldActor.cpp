// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityCharacterHoldActor.h"

#include "GameFramework/Character.h"

UAbilityCharacterHoldActor::UAbilityCharacterHoldActor() :
	PickUpSphereRadius(50.f)
{
	AbilityInputID = EAbilityInputID::Interact;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.HoldActor")));
}

void UAbilityCharacterHoldActor::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
    	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
    }
    
    ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());

	const FVector PickUpLoc = Character->GetActorLocation() + FVector(0.f, 0.f, -17.5f) + (Character->GetActorForwardVector() * 32.5f);
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(ActorInfo->AvatarActor.Get());
	FHitResult OutHit;

	const bool bHit = GetWorld()->SweepSingleByChannel(OutHit, PickUpLoc, PickUpLoc,
			FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(PickUpSphereRadius), QueryParams);

	// DrawDebugSphere(GetWorld(), PickUpLoc, PickUpSphereRadius, 12, FColor(0, 0, 0, 255), true, 2.f);

	if(GEngine && bHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow,
		                                 FString::Printf(TEXT("Colliding with %s"), *OutHit.GetActor()->GetName()));	
	}
}

bool UAbilityCharacterHoldActor::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UAbilityCharacterHoldActor::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (ActorInfo != nullptr && ActorInfo->AvatarActor != nullptr)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}
}

void UAbilityCharacterHoldActor::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}