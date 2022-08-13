#pragma once

#include "CreatureOasis/CreatureOasis.h"
#include "CreatureOasis/Objects/FuzzyActionCalculationObject.h"

#include "CreatureStatCalculationLibraryEntry.Generated.h"

USTRUCT(BlueprintType)
struct FCreatureStatCalculationLibraryEntry
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UFuzzyActionCalculationObject> FuzzyActionCalculationObject;

	// Used when FuzzyActionCalculationObject is empty
	UPROPERTY(EditAnywhere)
	ECheckCompareQuery CheckCompareQuery;

	// Used when FuzzyActionCalculationObject is empty
	UPROPERTY(EditAnywhere)
	float ValToUseWhenComparing;
};