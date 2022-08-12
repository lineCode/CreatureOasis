// Fill out your copyright notice in the Description page of Project Settings.


#include "GardenStaticsBlueprintLibrary.h"

#include "CreatureOasis/GameModes/BaseGardenGameMode.h"
#include "CreatureOasis/Structs/ProjectSettings/GardenSettings.h"

ABaseGardenGameMode* UGardenStaticsBlueprintLibrary::GetGardenGameMode(const UObject* WorldContextObject)
{
	const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	return Cast<ABaseGardenGameMode>(World->GetAuthGameMode());
}

FString UGardenStaticsBlueprintLibrary::GetRandomCreatureName()
{
	const UGardenSettings* GardenSettings = GetDefault<UGardenSettings>();
	const TArray<FString>& StringArray = GardenSettings->CreatureNameStringArray;
	if (StringArray.IsEmpty())
	{
		return "";
	}
	return StringArray[FMath::RandRange(0, StringArray.Max() - 1)];
}
