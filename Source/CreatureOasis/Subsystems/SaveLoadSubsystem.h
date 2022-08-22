// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureOasis/Objects/SaveGames/CreatureOasisSaveGame.h"

#include "SaveLoadSubsystem.generated.h"

class UGardenSettings;

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API USaveLoadSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USaveLoadSubsystem();

	// Garden save methods
	UFUNCTION(BlueprintCallable)
	void PrepareGardenSaveGame();
	void UpdateSaveGameWithGardenObjects(const TSharedPtr<FJsonObject> InGardenRootJsonObject);
	void UpdateSaveGameWithCreatures(const TSharedPtr<FJsonObject> InGardenRootJsonObject);

	// Garden load methods
	UFUNCTION(BlueprintCallable)
	void LoadGardenUsingSaveObject();
	void LoadAllGardenObjects(const TSharedPtr<FJsonValue> InRootJsonObject, const UGardenSettings* InGardenSettings) const;
	void LoadAllCreatures(const TSharedPtr<FJsonValue> InRootJsonObject, const UGardenSettings* InGardenSettings) const;

	// Race track load/save methods
	UFUNCTION(BlueprintCallable)
	void UpdateSaveGameWithActiveTrackGenerator();
	UFUNCTION(BlueprintCallable)
	void LoadTrackFromSaveGame();

	// General save-game methods
	UFUNCTION(BlueprintCallable)
	void WriteSaveGameToDisk() const;
	UFUNCTION(BlueprintCallable)
	void LoadSaveGameFromDisk();
	
protected:
	void InitAttributesFromJsonObject(UAbilitySystemComponent* AbilitySystemComponent, const TSharedPtr<FJsonObject> JsonObject) const;
	TSharedPtr<FJsonObject> SerializeAttributesIntoJsonObject(UAbilitySystemComponent* AbilitySystemComponent);
	
	UPROPERTY()
	UCreatureOasisSaveGame* CreatureSaveGame;

	UPROPERTY()
	FString LoadedSlotName;
};
