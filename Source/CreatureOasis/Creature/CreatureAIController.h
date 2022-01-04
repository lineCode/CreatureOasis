// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CreatureAIController.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API ACreatureAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACreatureAIController();

	void MoveForward() const;
	void RotateGraduallyTowardsTarget(const FVector TargetLocation) const;
	void RotateGraduallyTowardsTarget(const AActor* TargetActor) const;

	bool IsCreatureAtLocation(const FVector TargetLocation, const float AcceptableRadius = 5.f, const bool bAddCreatureRadius = true) const;

private:
	const class ACreatureCharacter* CreatureCharacter;  
};
