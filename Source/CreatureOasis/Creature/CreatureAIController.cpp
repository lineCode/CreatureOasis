// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureAIController.h"

#include "CreatureCharacter.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"

ACreatureAIController::ACreatureAIController()
{
	CreatureCharacter = Cast<ACreatureCharacter>(GetPawn());
}

void ACreatureAIController::MoveForward() const
{
	GetPawn()->AddMovementInput(GetPawn()->GetActorForwardVector(), 1.f);
}

void ACreatureAIController::RotateGraduallyTowardsTarget(const FVector TargetLocation) const
{
	FVector TargetDirection = (TargetLocation - GetPawn()->GetActorLocation());
	TargetDirection.Z = 0;
	
	const FRotator ResultRot = FMath::Lerp(GetPawn()->GetActorRotation(), TargetDirection.Rotation(), GetWorld()->GetDeltaSeconds());
	
	GetPawn()->SetActorRotation(ResultRot);
}

void ACreatureAIController::RotateGraduallyTowardsTarget(const AActor* TargetActor) const
{
	RotateGraduallyTowardsTarget(TargetActor->GetActorLocation());
}

bool ACreatureAIController::IsAtLocation(const FVector TargetLocation, const float AcceptableRadius, const bool bAddCreatureRadius) const
{
	float RadiusToUse = AcceptableRadius;
	if (bAddCreatureRadius && IsValid(CreatureCharacter))
	{
		RadiusToUse += CreatureCharacter->GetCapsuleComponent()->GetScaledCapsuleRadius();
	}
	
	return FVector::Dist2D(GetPawn()->GetActorLocation(), TargetLocation) < RadiusToUse;
}

bool ACreatureAIController::IsRotatedTowardsLocation(const FVector TargetLocation, const float Tolerance) const
{
	FVector TargetDirection = (TargetLocation - GetPawn()->GetActorLocation());
	TargetDirection.Z = 0;

	return FMath::Abs(GetPawn()->GetActorRotation().Yaw - TargetDirection.Rotation().Yaw) <= Tolerance;
}
