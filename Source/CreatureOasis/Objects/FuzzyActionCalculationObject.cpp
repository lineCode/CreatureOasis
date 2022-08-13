// Fill out your copyright notice in the Description page of Project Settings.


#include "FuzzyActionCalculationObject.h"

#include "AbilitySystemComponent.h"
#include "CreatureOasis/Subsystems/GardenActorsSubsystem.h"

float UFuzzyActionCalculationObject::CalculateScore_Implementation(UWorld* World, AAIController* AIController,
	const UAbilitySystemComponent* BaseAbilitySystemComponent)
{
	return 0.f;
}

UGardenActorsSubsystem* UFuzzyActionCalculationObject::GetGardenActorsSubsystem(const UWorld* World) const
{
	if (!IsValid(World))
	{
		return nullptr;
	}
	
	return World->GetSubsystem<UGardenActorsSubsystem>();
}
