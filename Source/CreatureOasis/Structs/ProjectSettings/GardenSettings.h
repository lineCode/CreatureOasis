#pragma once

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
};