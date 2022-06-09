// Fill out your copyright notice in the Description page of Project Settings.


#include "GardenStaticsBlueprintLibrary.h"

#include "CreatureOasis/GameModes/BaseGardenGameMode.h"

ABaseGardenGameMode* UGardenStaticsBlueprintLibrary::GetGardenGameMode(const UObject* WorldContextObject)
{
	const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	return Cast<ABaseGardenGameMode>(World->GetAuthGameMode());
}