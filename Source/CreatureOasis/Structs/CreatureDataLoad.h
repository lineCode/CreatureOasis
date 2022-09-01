#pragma once
#include "GameplayTagContainer.h"

#include "CreatureDataLoad.Generated.h"

USTRUCT(BlueprintType)
struct FCreatureDataLoad
{
	GENERATED_BODY()
	
	// Appearance Component
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag ColorTag = FGameplayTag::RequestGameplayTag("Color.Normal");
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor InitialPrimaryColor = FLinearColor(0.f, 0.f, 0.f, 1.f);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor InitialSecondaryColor = FLinearColor(0.f, 0.f, 0.f, 1.f);
	
	// Expression Component
	UPROPERTY()
	FGameplayTag InitialEyeTag;
	UPROPERTY()
	FGameplayTag InitialMouthTag;

	UPROPERTY()
	FGameplayTag EvolutionStateTag;
	
	// Personality Component
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName CreatureName = TEXT("");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGuid UniqueIdentifier;
};