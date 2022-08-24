#pragma once

#include "EvolutionStateData.Generated.h"

USTRUCT(BlueprintType)
struct FEvolutionStateData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMesh* SkeletalMesh = nullptr;
};