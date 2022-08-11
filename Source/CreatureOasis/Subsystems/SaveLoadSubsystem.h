// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureOasis/Objects/SaveGames/CreatureOasisSaveGame.h"

#include "SaveLoadSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API USaveLoadSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USaveLoadSubsystem();
	
	UFUNCTION(BlueprintCallable)
	void UpdateSaveGameWithGardenObjects();

	UFUNCTION(BlueprintCallable)
	void LoadGardenObjectsFromSaveGame();

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
