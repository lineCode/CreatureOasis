// Fill out your copyright notice in the Description page of Project Settings.

#include "GardenActor.h"

#include "CreatureOasis/Subsystems/GardenActorsSubsystem.h"

AGardenActor::AGardenActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGardenActor::InitializeFromSaveGame(const FGameplayTag InMainTypeTag, const FGameplayTag InSubTypeTag)
{
	MainTypeTag = InMainTypeTag;
	SubTypeTag = InSubTypeTag;
}

FGameplayTag AGardenActor::GetMainTypeTag() const
{
	return MainTypeTag;
}

FGameplayTag AGardenActor::GetSubTypeTag() const
{
	return SubTypeTag;
}

void AGardenActor::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetSubsystem<UGardenActorsSubsystem>()->AddGardenActor(MainTypeTag, this);
}

void AGardenActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetSubsystem<UGardenActorsSubsystem>()->RemoveGardenActor(MainTypeTag, this);
}
