// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDynamicBTAction.h"

#include "CreatureOasis/Subsystems/GardenActorsSubsystem.h"

float UBaseDynamicBTAction::CalculateScore_Implementation(UWorld* World, AAIController* AIController, const class UBaseAbilitySystemComponent* BaseAbilitySystemComponent)
{
	return 0.f;
}

UBehaviorTree* UBaseDynamicBTAction::GetBehaviorTreeToRun_Implementation()
{
	return BehaviorTreeToRun;
}

UGardenActorsSubsystem* UBaseDynamicBTAction::GetGardenActorsSubsystem(const UWorld* World) const
{
	if (!IsValid(World))
	{
		return nullptr;
	}
	
	return World->GetSubsystem<UGardenActorsSubsystem>();
}
