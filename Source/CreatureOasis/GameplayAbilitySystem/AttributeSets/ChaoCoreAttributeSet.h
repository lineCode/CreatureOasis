#pragma once

#include "ChaoStatsAttributeSet.h"

#include "ChaoCoreAttributeSet.generated.h"

UCLASS()
class CREATUREOASIS_API UChaoCoreAttributeSet : public UChaoStatsAttributeSet
{
	GENERATED_BODY()
	
public:
	// Attribute layout inspired by "Fusion's Chao Editor"

	//// General
	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|General")
	FGameplayAttributeData Happiness;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, Happiness);

	//// Reincarnations and lifespan
	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|ReincarnationsAndLifespan")
	FGameplayAttributeData Reincarnations;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, Reincarnations);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|ReincarnationsAndLifespan")
	FGameplayAttributeData RemainingLife;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, RemainingLife);
	
	//// Evolutions
	// Run <-> Power
    UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|Evolution")
    FGameplayAttributeData RunPower;
    ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, RunPower);
	// Swim <-> Fly
	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|Evolution")
	FGameplayAttributeData SwimFly;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, SwimFly);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|Evolution")
	FGameplayAttributeData Magnitude;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, Magnitude);

	//// Personality

	//// Health
	
	//// Emotions and Behaviours
	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|EmotionsAndBehaviours")
	FGameplayAttributeData DesireToMate;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, DesireToMate);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|EmotionsAndBehaviours")
	FGameplayAttributeData Hunger;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, Hunger);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|EmotionsAndBehaviours")
	FGameplayAttributeData Sleepiness;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, Sleepiness);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|EmotionsAndBehaviours")
	FGameplayAttributeData Boredom;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, Boredom);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|EmotionsAndBehaviours")
	FGameplayAttributeData Energy;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, Energy);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|EmotionsAndBehaviours")
	FGameplayAttributeData Joy;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, Joy);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|EmotionsAndBehaviours")
	FGameplayAttributeData UrgeToCry;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, UrgeToCry);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|EmotionsAndBehaviours")
	FGameplayAttributeData Fear;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, Fear);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|EmotionsAndBehaviours")
    FGameplayAttributeData Dizziness;
    ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, Dizziness);

	//// Character bonds
	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|EmotionsAndBehaviours")
	FGameplayAttributeData PlaceholderCharacterBond;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, PlaceholderCharacterBond);
};
