// Fill out your copyright notice in the Description page of Project Settings.

#include "CreatureCharacter.h"

#include "AbilitySystemComponent.h"
#include "CreatureAIController.h"
#include "GameplayEffect.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "CreatureOasis/Structs/CreaturePassiveStatEffectTableRow.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACreatureCharacter::ACreatureCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	HoldableAnchor = CreateDefaultSubobject<UHoldableAnchorComponent>(TEXT("HoldableAnchor"));
	HoldableAnchor->SetupAttachment(GetMesh());
	
	AppearanceComponent = CreateDefaultSubobject<UCreatureAppearanceComponent>(TEXT("AppearanceComponent"));
	ExpressionComponent = CreateDefaultSubobject<UCreatureExpressionComponent>(TEXT("ExpressionComponent"));
}

// Called when the game starts or when spawned
void ACreatureCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACreatureCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	GetAbilitySystemComponent()->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Interrupted"));

	CreatureAIController->BehaviorTreeComponent->RestartTree();

	GetMovementComponent()->Deactivate();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACreatureCharacter::EndBeingHold_Implementation()
{
	GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Interrupted"));

	GetMovementComponent()->Activate();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
