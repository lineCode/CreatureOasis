#pragma once

#include "ChaoStatsAttributeSet.h"

#include "ChaoCoreAttributeSet.generated.h"

UCLASS()
class CREATUREOASIS_API UChaoCoreAttributeSet : public UChaoStatsAttributeSet
{
	GENERATED_BODY()
	
public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void InitFromMetaDataTable(const UDataTable* DataTable) override;
	
	const float MinValue = 0.f;
	const float MaxValue = 100.f;

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
	
	//// Health
	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|Health")
	FGameplayAttributeData Cough;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, Cough);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|Health")
	FGameplayAttributeData Cold;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, Cold);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|Health")
	FGameplayAttributeData Rash;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, Rash);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|Health")
	FGameplayAttributeData RunningNose;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, RunningNose);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|Health")
	FGameplayAttributeData Hiccups;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, Hiccups);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|Health")
	FGameplayAttributeData StomachAche;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, StomachAche);
	
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
	FGameplayAttributeData Tiredness;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, Tiredness);
	
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
	FGameplayAttributeData Relax;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, Relax);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|EmotionsAndBehaviours")
	FGameplayAttributeData Stress;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, Stress);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|EmotionsAndBehaviours")
	FGameplayAttributeData Lonely;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, Lonely);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes|ChaoCore|EmotionsAndBehaviours")
	FGameplayAttributeData Anger;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, Anger);
	
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

	//// Movement component use
	UPROPERTY(BlueprintReadOnly, Category="Attributes|MovementComponent|Rotation")
	FGameplayAttributeData RotationRateYaw;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, RotationRateYaw);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|MovementComponent")
	FGameplayAttributeData MaxWalkSpeed;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, MaxWalkSpeed);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|MovementComponent")
	FGameplayAttributeData MaxSwimSpeed;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, MaxSwimSpeed);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes|MovementComponent")
	FGameplayAttributeData MaxFlySpeed;
	ATTRIBUTE_ACCESSORS(UChaoCoreAttributeSet, MaxFlySpeed);
};
