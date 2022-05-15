// Fill out your copyright notice in the Description page of Project Settings.

#include "CreatureCharacter.h"

#include "GameplayEffect.h"
#include "Components/BoxComponent.h"
#include "CreatureOasis/Structs/CreaturePassiveStatEffectTableRow.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACreatureCharacter::ACreatureCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	PickUpBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PickUpBox"));
	PickUpBox->SetupAttachment(RootComponent);
	
	PickUpAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("PickUpAnchor"));
	PickUpAnchor->SetupAttachment(GetMesh());

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

bool ACreatureCharacter::StartHold_Implementation(AActor* InstigatorActor)
{
	return IHoldableInterface::StartHold_Implementation(InstigatorActor);
}

bool ACreatureCharacter::EndHold_Implementation()
{
	return IHoldableInterface::EndHold_Implementation();
}