#pragma once

#include "BaseAttributeSet.h"

#include "ChaoStatsAttributeSet.generated.h"

UCLASS()
class CREATUREOASIS_API UChaoStatsAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()
	
public:

	//// Stats

	// Swim
	UPROPERTY(BlueprintReadOnly, Category="Attributes|CreatureStats")
	FGameplayAttributeData SwimPoints;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, SwimPoints);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|CreatureStats")
	FGameplayAttributeData SwimLvl;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, SwimLvl);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|CreatureStats")
	FGameplayAttributeData SwimLvlBar;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, SwimLvlBar);
	
	// Fly
	
	// Power

	
	// Stamina

	
	// Intelligence

	
	// Luck
	
	
};
