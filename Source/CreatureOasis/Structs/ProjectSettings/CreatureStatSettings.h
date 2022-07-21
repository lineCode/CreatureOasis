// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "CreatureStatSettings.generated.h"

struct FGameplayAttribute;

/**
 * 
 */
UCLASS(Config=Game, defaultconfig, meta = (DisplayName="Creature Stat Game Settings"))
class CREATUREOASIS_API UCreatureStatSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	TMap<FGameplayTag, FGameplayAttribute> StatTagRelationArray;
};
