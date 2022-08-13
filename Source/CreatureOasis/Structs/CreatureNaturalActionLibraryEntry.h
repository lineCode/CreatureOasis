#pragma once

#include "BehaviorTree/BehaviorTree.h"
#include "CreatureOasis/Objects/FuzzyActionCalculationObject.h"
#include "AttributeSet.h"

#include "CreatureNaturalActionLibraryEntry.Generated.h"

USTRUCT(BlueprintType)
struct FCreatureFuzzyActionData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UFuzzyActionCalculationObject> FuzzyActionCalculationObject;

	UPROPERTY(EditAnywhere)
	float ResultValueToUseOnMissingCalculationObject;
	
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTreeAction;
};

USTRUCT(BlueprintType)
struct FCreatureFuzzyActionStatCollection
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TArray<FCreatureFuzzyActionData> CreatureFuzzyActionDataArray;
};

USTRUCT(BlueprintType)
struct FCreatureNaturalActionLibraryEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TMap<FGameplayAttribute, FCreatureFuzzyActionStatCollection> CreatureStatChecks;
};