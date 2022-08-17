#pragma once

#include "CreatureOasis/CreatureOasis.h"
#include "CreatureOasis/Objects/FuzzyActionCalculationObject.h"

#include "CreatureStatCalculationLibraryEntry.Generated.h"

USTRUCT(BlueprintType)
struct FCreatureStatCalculationLibraryEntry
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, meta = (EditCondition = "!bUseCustomValues"))
	TSubclassOf<UFuzzyActionCalculationObject> FuzzyActionCalculationObject;

	UPROPERTY(EditAnywhere)
    bool bUseCustomValues;

    UPROPERTY(EditAnywhere, meta = (ClampMin=0.f, ClampMax=100.f, EditCondition = "bUseCustomValues"))
    float CustomResultValue;

    UPROPERTY(EditAnywhere, Category = Condition, meta = (EditCondition = "bUseCustomValues"))
    float CustomResultValueRandomDeviation;

    // Owning attribute should have at least this value before we decide on applying this action
    UPROPERTY(EditAnywhere, meta = (ClampMin=0.f, ClampMax=100.f))
    float AttributeMinValue;
    
    // 0.f = 0% chance | 0.5 = 50% chance | 1.f = 100% chance
    UPROPERTY(EditAnywhere, meta = (ClampMin=0.f, ClampMax=1.f))
    float ChanceToApply = 1.f;
    
    UPROPERTY(EditAnywhere)
    UBehaviorTree* BehaviorTreeAction;

    float GetCustomResultValue() const
    {
        if (CustomResultValueRandomDeviation > 0.f)
        {
            return FMath::FRandRange(CustomResultValue - CustomResultValueRandomDeviation, CustomResultValue + CustomResultValueRandomDeviation);
        }
        return CustomResultValue;
    }
};