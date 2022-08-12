// Fill out your copyright notice in the Description page of Project Settings.


#include "CreaturePersonalityComponent.h"


UCreaturePersonalityComponent::UCreaturePersonalityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCreaturePersonalityComponent::SetCreatureName(FString NewNameString)
{
	CreatureName = NewNameString;
}

FString UCreaturePersonalityComponent::GetCreatureName() const
{
	return CreatureName;
}

void UCreaturePersonalityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UCreaturePersonalityComponent::LoadCreatureData_Implementation(const FCreatureDataLoad& CreatureDataLoad)
{
	SetCreatureName(CreatureDataLoad.CreatureName);
}

void UCreaturePersonalityComponent::GatherCreatureData_Implementation(FCreatureDataLoad& CreatureDataLoad)
{
	CreatureDataLoad.CreatureName = GetCreatureName();
}
