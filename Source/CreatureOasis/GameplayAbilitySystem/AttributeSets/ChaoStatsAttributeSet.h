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
	FGameplayAttributeData SwimLvlProgress;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, SwimLvlProgress);
	
	// Fly
	UPROPERTY(BlueprintReadOnly, Category="Attributes|CreatureStats")
	FGameplayAttributeData FlyPoints;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, FlyPoints);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|CreatureStats")
	FGameplayAttributeData FlyLvl;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, FlyLvl);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|CreatureStats")
	FGameplayAttributeData FlyLvlProgress;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, FlyLvlProgress);

	// Run
	UPROPERTY(BlueprintReadOnly, Category="Attributes|CreatureStats")
	FGameplayAttributeData RunPoints;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, RunPoints);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|CreatureStats")
	FGameplayAttributeData RunLvl;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, RunLvl);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|CreatureStats")
	FGameplayAttributeData RunLvlProgress;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, RunLvlProgress);
	
	// Power
	UPROPERTY(BlueprintReadOnly, Category="Attributes|CreatureStats")
	FGameplayAttributeData PowerPoints;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, PowerPoints);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|CreatureStats")
	FGameplayAttributeData PowerLvl;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, PowerLvl);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|CreatureStats")
	FGameplayAttributeData PowerLvlProgress;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, PowerLvlProgress);
	
	// Stamina
	UPROPERTY(BlueprintReadOnly, Category="Attributes|CreatureStats")
	FGameplayAttributeData StaminaPoints;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, StaminaPoints);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|CreatureStats")
	FGameplayAttributeData StaminaLvl;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, StaminaLvl);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|CreatureStats")
	FGameplayAttributeData StaminaLvlProgress;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, StaminaLvlProgress);
	
	// Intelligence

	
	// Luck
	
	
};
