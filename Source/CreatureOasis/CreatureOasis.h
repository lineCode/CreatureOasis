// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/* used for automatically binding abilities to key binds when desired */
UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	None			UMETA(DisplayName = "None"),
	Confirm			UMETA(DisplayName = "Confirm"),
	Cancel			UMETA(DisplayName = "Cancel"),
	Ability1		UMETA(DisplayName = "Ability1"),
	Ability2		UMETA(DisplayName = "Ability2"),
	Ability3		UMETA(DisplayName = "Ability3"),
	Ability4		UMETA(DisplayName = "Ability4"),
	Ability5		UMETA(DisplayName = "Ability5"),
	Jump			UMETA(DisplayName = "Jump"),
	Interact		UMETA(DisplayName = "Interact")
};

/**
 * Used for determining what kind of Comparative check we should use
 */
UENUM(BlueprintType)
enum class ECheckCompareQuery : uint8
{
	Less				UMETA(DisplayName = "Less"),
	LessOrEqual			UMETA(DisplayName = "LessOrEqual"),
	Equal				UMETA(DisplayName = "Equal"),
	Greater				UMETA(DisplayName = "Greater"),
	GreaterOrEqual		UMETA(DisplayName = "GreaterOrEqual")
};