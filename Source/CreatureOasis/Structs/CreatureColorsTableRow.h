#pragma once
#include "GameplayTagContainer.h"

#include "CreatureColorsTableRow.generated.h"

USTRUCT(BlueprintType)
struct FCreatureColorsTableRow
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CreatureColors")
	FGameplayTag GameplayTagColor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CreatureColors")
	FLinearColor PrimaryColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CreatureColors")
	FLinearColor SecondaryColor;
};
