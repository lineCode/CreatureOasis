#pragma once
#include "GameplayTagContainer.h"

#include "CreatureDataLoad.Generated.h"

USTRUCT(BlueprintType)
struct FCreatureDataLoad
{
	GENERATED_BODY()
	
	// Appearance Component
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor InitialPrimaryColor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor InitialSecondaryColor;
	
	// Expression Component
	UPROPERTY()
	FGameplayTag InitialEyeTag;
	UPROPERTY()
	FGameplayTag InitialMouthTag;
	
	// Personality Component
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString CreatureName;

};