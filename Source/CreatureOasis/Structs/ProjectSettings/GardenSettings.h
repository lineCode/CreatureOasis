﻿#pragma once

#include "CreatureOasis/Structs/CreatureNaturalActionLibraryEntry.h"
#include "CreatureOasis/Structs/CreatureStatCalculationLibraryEntry.h"

#include "GardenSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, defaultconfig, meta = (DisplayName="Garden Settings"))
class UGardenSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	int32 MaxCreatures;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	int32 AmountOfStartingCreaturesToSpawnOnEmptySave;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	TMap<FGameplayTag, TSubclassOf<AActor>> GardenActorTypeClassRelationMap;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Creature")
	TArray<FString> CreatureNameStringArray;

	// Actions the creature can do naturally based on its stats and without being interrupted (Actions Creature can take while thinking for itself)
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Creature")
	TMap<FGameplayTag, FCreatureNaturalActionLibraryEntry> CreatureNaturalActionLibrary;

	// Used when deciding which action set to take from the CreatureNaturalActionLibrary defined earlier
	// This so we've got more control in deciding which actions should play when, also to improve performance 
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Creature")
	TMap<FGameplayAttribute, FCreatureStatCalculationLibraryEntry> CreatureStatCalculationLibrary;
};