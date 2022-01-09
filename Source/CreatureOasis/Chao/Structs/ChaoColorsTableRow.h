#pragma once
#include "GameplayTagContainer.h"

#include "ChaoColorsTableRow.generated.h"

USTRUCT(BlueprintType)
struct FChaoColorsTableRow
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="ChaoColors")
	FGameplayTag GameplayTagColor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="ChaoColors")
	FLinearColor PrimaryColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="ChaoColors")
	FLinearColor SecondaryColor;
};
