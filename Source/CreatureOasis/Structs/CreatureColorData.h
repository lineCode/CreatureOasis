#pragma once

#include "CreatureColorData.Generated.h"

USTRUCT(BlueprintType)
struct FCreatureColorData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor PrimaryColor = FLinearColor(0.f, 0.f, 0.f, 1.f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor SecondaryColor = FLinearColor(0.f, 0.f, 0.f, 1.f);
};

