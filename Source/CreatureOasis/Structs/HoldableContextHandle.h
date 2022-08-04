// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayEffectTypes.h"
#include "HoldableContextHandle.generated.h"

/**
 * Will hold Holdable custom Context data for FGameplayEventData, ContextData
 */
USTRUCT(BlueprintType)
struct CREATUREOASIS_API FHoldableContextHandle : public FGameplayEffectContextHandle
{
	GENERATED_USTRUCT_BODY()

	/** Tag of the event that triggered this */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HoldableContextHandle)
	AActor* Target;
};
