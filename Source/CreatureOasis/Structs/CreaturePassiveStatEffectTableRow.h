#pragma once

#include "AttributeSet.h"
#include "Engine/DataTable.h"

#include "CreaturePassiveStatEffectTableRow.generated.h"

USTRUCT(BlueprintType)
struct FCreaturePassiveStatEffectTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CreaturePassiveStatEffectTableRow")
	FGameplayAttribute Attribute;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CreaturePassiveStatEffectTableRow")
	float Rate;

	/* Ranges from 0.0 to 1.0 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CreaturePassiveStatEffectTableRow")
	float ChanceToApply;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CreaturePassiveStatEffectTableRow")
	float Modifier;
};
