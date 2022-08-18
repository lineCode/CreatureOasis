// Fill out your copyright notice in the Description page of Project Settings.

#include "CreatureCharacter.h"

#include "AbilitySystemComponent.h"
#include "CreatureAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Components/CapsuleComponent.h"
#include "CreatureOasis/GameplayAbilitySystem/BaseAbilitySystemComponent.h"
#include "CreatureOasis/Subsystems/GardenActorsSubsystem.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACreatureCharacter::ACreatureCharacter()
	: CharacterCurrentlyHoldingUs(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;
	
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void ACreatureCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetSubsystem<UGardenActorsSubsystem>()->AddGardenActor(FGameplayTag::RequestGameplayTag("Type.Creature"), this);
}

void ACreatureCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetSubsystem<UGardenActorsSubsystem>()->RemoveGardenActor(FGameplayTag::RequestGameplayTag("Type.Creature"), this);
}

// Called to bind functionality to input
void ACreatureCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACreatureCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	CreatureAIController = Cast<ACreatureAIController>(NewController);
}

void ACreatureCharacter::StartBeingHold_Implementation(AGASCharacter* InstigatorCharacter)
{
	GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Interrupted.BeingHold"));

	// make sure other abilities know we have just Cancelled holding an object
	const FGameplayEventData GameplayEventData = FGameplayEventData();
	AbilitySystemComponent->HandleGameplayEvent(FGameplayTag::RequestGameplayTag("Event.HoldCancel"), &GameplayEventData);

	GetMovementComponent()->StopMovementImmediately();
	
	GetCharacterMovement()->DisableMovement();
	
	GetCapsuleComponent()->SetCollisionProfileName(FName("IgnoreOnlyCreature"));

	CharacterCurrentlyHoldingUs = InstigatorCharacter;
}

void ACreatureCharacter::EndBeingHold_Implementation()
{
	GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Interrupted.BeingHold"));

	if (CharacterCurrentlyHoldingUs->GetVelocity() == FVector::Zero() && !CharacterCurrentlyHoldingUs->bWasJumping)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
	else
	{
		// Character holding us has thrown us
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);

		const FVector Vel = (CharacterCurrentlyHoldingUs->GetActorForwardVector() + (GetActorUpVector() * 2.f)).GetSafeNormal() * 400.f;
		GetCharacterMovement()->AddImpulse(Vel, true);
		AbilitySystemComponent->ApplyGameplayEffectToSelf(EffectToApplyOnBeingThrown.GetDefaultObject(), 0.f, FGameplayEffectContextHandle());
	}

	GetCapsuleComponent()->SetCollisionProfileName(FName("Creature"));

	CharacterCurrentlyHoldingUs = nullptr;
}

AGASCharacter* ACreatureCharacter::GetCharacterCurrentlyHoldingUs_Implementation()
{
	return CharacterCurrentlyHoldingUs;
}