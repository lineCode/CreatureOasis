// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CreatureOasis/GameplayAbilitySystem/AttributeSets/ChaoCoreAttributeSet.h"
#include "GameFramework/SaveGame.h"
#include "Dom/JsonObject.h"
#include "CreatureOasisSaveGame.generated.h"

// USTRUCT(BlueprintType)
// struct FBaseSaveInfo
// {
// 	GENERATED_BODY()
// };
//
// USTRUCT(BlueprintType)
// struct FGASAttributesSaveInfo : public FBaseSaveInfo
// {
// 	GENERATED_BODY()
// 	
// 	UChaoCoreAttributeSet ChaoCoreAttributeSet;
// };
//
// USTRUCT(BlueprintType)
// struct FCreatureSaveInfo : public FGASAttributesSaveInfo
// {
// 	GENERATED_BODY()
// 	
// 	FString Name;
//
// 	FGameplayTagContainer PersonalityTags;
// 	
// 	FGameplayTagContainer InitialExpressionTags;
//
// 	// Hats, etc
// 	FGameplayTagContainer AccessoryTags;
// };
//
// USTRUCT(BlueprintType)
// struct FGardenObjectSaveInfo : public FGASAttributesSaveInfo
// {
// 	GENERATED_BODY()
//
// 	FGameplayTag MainTypeTag;
// 	FGameplayTag SubTypeTag;
// };

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UCreatureOasisSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UCreatureOasisSaveGame();

	UPROPERTY(VisibleAnywhere, Category=Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category=Basic)
	uint32 UserIndex;

	// GardenLevelTag / CreatureInfo relation
	// TMultiMap<FGameplayTag, FCreatureSaveInfo> CreatureSaveInfoMultiMap;

	// TMap<FGameplayTag, TArray<FGameplayTag>> GardenObjectsMap;

	UPROPERTY(VisibleAnywhere, Category=Basic)
	FString GardenActorsJsonString;
};
