// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityCharacterHoldActor.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "CreatureOasis/BlueprintLibraries/CreatureOasisBlueprintLibrary.h"
#include "CreatureOasis/Components/HoldableAnchorComponent.h"
#include "CreatureOasis/GameplayAbilitySystem/GASCharacter.h"
#include "CreatureOasis/Interfaces/HoldableAnchorInterface.h"
#include "CreatureOasis/Interfaces/HoldableInterface.h"
#include "GameFramework/Character.h"

UAbilityCharacterHoldActor::UAbilityCharacterHoldActor()
	: ActiveGameplayTag(FGameplayTag::RequestGameplayTag(FName("Ability.HoldActor")))
{
	AbilityInputID = EAbilityInputID::Interact;
	
	AbilityTags.AddTag(ActiveGameplayTag);
	ActivationOwnedTags.AddTag(ActiveGameplayTag);

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag = FGameplayTag::RequestGameplayTag("Event.HoldActor");
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	
	AbilityTriggers.Add(TriggerData);
}

void UAbilityCharacterHoldActor::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
    	EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
    }

	UAbilityTask_WaitGameplayEvent* Task = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, FGameplayTag::RequestGameplayTag("Event.HoldCancel"));
	Task->EventReceived.AddDynamic(this, &UAbilityCharacterHoldActor::CancelAbilityEvent);
	Task->ReadyForActivation();
	
	AGASCharacter* AvatarCharacter = CastChecked<AGASCharacter>(ActorInfo->AvatarActor.Get());
	
	UHoldableAnchorComponent* HoldableAnchorComponent = AvatarCharacter->FindComponentByClass<UHoldableAnchorComponent>();
	if (IsValid(HoldableAnchorComponent))
	{
		AActor* ActorToHold = nullptr;

		if (TriggerEventData != nullptr)
		{
			// FGameplayEventData TempPayload = *TriggerEventData; // As done in AbilityTak_WaitGameplayEvent, dereference and copy data due to how UStruct works
			ActorToHold = const_cast<AActor*>(TriggerEventData->Target); // Bad; why you do this to me Unreal???? Blueprints lets me alter payload data just fine
		}

		if (ActorToHold == nullptr)
		{
			ActorToHold = HoldableAnchorComponent->DetectHoldableActor();
		}
		
		if (IsValid(ActorToHold))
		{
			FGameplayTagContainer NewTargetTags;
			
			AActor* TargetHoldable = DoWeTakeHoldableFromTarget(ActorToHold);
			if (IsValid(TargetHoldable))
			{
				ActorToHold = TargetHoldable;
				
				NewTargetTags.AddTag(IHoldableInterface::Execute_GetTypeOfActor(ActorToHold));
				NewTargetTags.AddTag(FGameplayTag::RequestGameplayTag("State.Holdable.TakenAway"));
			}
			
			// Make sure that when the ActorToHold is already being held by a GASCharacter we Detach from it first
			// Example: Player holds an Actor that it wants to give to something else, make sure player fires HoldCancel
			const AGASCharacter* HolderOfActorToHold = IHoldableInterface::Execute_GetCharacterCurrentlyHoldingUs(ActorToHold);
			if (IsValid(HolderOfActorToHold))
			{
				FGameplayEventData GameplayEventData = FGameplayEventData();
				GameplayEventData.Target = ActorToHold;
				GameplayEventData.TargetTags = NewTargetTags;
				GameplayEventData.Instigator = AvatarCharacter;
				GameplayEventData.InstigatorTags = FGameplayTagContainer(UCreatureOasisBlueprintLibrary::GetTypeTagAssignedToAbilitySystemComponent(AvatarCharacter->GetAbilitySystemComponent()));
				
				HolderOfActorToHold->GetAbilitySystemComponent()->HandleGameplayEvent(FGameplayTag::RequestGameplayTag("Event.HoldCancel"), &GameplayEventData);
			}
			
			IHoldableInterface::Execute_StartBeingHold(ActorToHold, AvatarCharacter);
		
			HoldableAnchorComponent->AttachHoldable(ActorToHold);
		}
		else
		{
			CancelAbility(Handle, ActorInfo, ActivationInfo, true);
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

void UAbilityCharacterHoldActor::CancelAbilityEvent(FGameplayEventData GameplayEventData)
{
	const FGameplayAbilityActorInfo AbilityActorInfo = GetActorInfo();
	CancelAbility(GetCurrentAbilitySpecHandle(), &AbilityActorInfo, CurrentActivationInfo, true);
}

AActor* UAbilityCharacterHoldActor::DoWeTakeHoldableFromTarget(AActor* Target)
{
	// If ActorToHold is an actor that is able to hold and is holding an actor we want his Actor instead
	if (Target->GetClass()->ImplementsInterface(UHoldableAnchorInterface::StaticClass())
		&& IHoldableAnchorInterface::Execute_IsHoldingActor(Target))
	{
		AActor* HeldActor = IHoldableAnchorInterface::Execute_GetHeldActorFromHoldableAnchorComponent(Target);

		if (Target->GetActorForwardVector().Dot(GetAvatarActorFromActorInfo()->GetActorForwardVector()) < -0.6f)
		{
			return HeldActor;
		}
	}

	return nullptr;
}
