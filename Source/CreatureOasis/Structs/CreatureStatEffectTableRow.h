#pragma once

#include "CreatureStatEffectTableRow.generated.h"

USTRUCT(BlueprintType)
struct FCreatureStatEffectTableRow
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CreatureColors")
	float Rate;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CreatureColors")
	float ToAdd;
};
