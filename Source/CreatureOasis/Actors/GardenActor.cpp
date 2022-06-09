// Fill out your copyright notice in the Description page of Project Settings.

#include "GardenActor.h"

#include "CreatureOasis/Subsystems/GardenActorsSubsystem.h"

AGardenActor::AGardenActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGardenActor::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetSubsystem<UGardenActorsSubsystem>()->AddGardenActor(GardenActorTypeTag, this);
}