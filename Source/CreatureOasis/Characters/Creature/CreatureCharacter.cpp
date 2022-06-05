// Fill out your copyright notice in the Description page of Project Settings.

#include "CreatureCharacter.h"

#include "AbilitySystemComponent.h"
#include "CreatureAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Components/CapsuleComponent.h"
#include "CreatureOasis/GameplayAbilitySystem/BaseAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACreatureCharacter::ACreatureCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void ACreatureCharacter::BeginPlay()
{
	Super::BeginPlay();
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

void ACreatureCharacter::StartBeingHold_Implementation(AActor* InstigatorActor)
{
	GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Interrupted.BeingHold"));
	CreatureAIController->BehaviorTreeComponent->RestartTree();

	AbilitySystemComponent->CancelAllAbilities();

	GetMovementComponent()->Deactivate();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACreatureCharacter::EndBeingHold_Implementation()
{
	GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Interrupted.BeingHold"));

	GetMovementComponent()->Activate();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
