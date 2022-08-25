#pragma once

#include "BaseAttributeSet.h"

#include "ChaoStatsAttributeSet.generated.h"

UCLASS()
class CREATUREOASIS_API UChaoStatsAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()
	
public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
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

	UPROPERTY(BlueprintReadOnly, Category="Attributes|CreatureStats")
	FGameplayAttributeData SwimProficiencyGrade;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, SwimProficiencyGrade);
	
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

	UPROPERTY(BlueprintReadOnly, Category="Attributes|CreatureStats")
	FGameplayAttributeData FlyProficiencyGrade;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, FlyProficiencyGrade);

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

	UPROPERTY(BlueprintReadOnly, Category="Attributes|CreatureStats")
	FGameplayAttributeData RunProficiencyGrade;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, RunProficiencyGrade);
	
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

	UPROPERTY(BlueprintReadOnly, Category="Attributes|CreatureStats")
	FGameplayAttributeData PowerProficiencyGrade;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, PowerProficiencyGrade);
	
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

	UPROPERTY(BlueprintReadOnly, Category="Attributes|CreatureStats")
	FGameplayAttributeData StaminaProficiencyGrade;
	ATTRIBUTE_ACCESSORS(UChaoStatsAttributeSet, StaminaProficiencyGrade);
	
	// Intelligence

	
	// Luck
	
	
};
