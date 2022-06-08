// Fill out your copyright notice in the Description page of Project Settings.

#include "GardenActor.h"

#include "CreatureOasis/BlueprintLibraries/GardenStaticsBlueprintLibrary.h"
#include "CreatureOasis/Objects/GardenActorsManager.h"

AGardenActor::AGardenActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGardenActor::BeginPlay()
{
	Super::BeginPlay();
	
	UGardenStaticsBlueprintLibrary::GetGardenActorsManager(GetWorld())
		->AddGardenActor(GardenActorTypeTag, this);
}