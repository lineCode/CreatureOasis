// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "ChaosDriveTableRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CREATUREOASIS_API FChaosDriveTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="ChaosDriveTableRow")
	FLinearColor ColorOverride;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="ChaosDriveTableRow")
	TSubclassOf<UGameplayEffect> OnUsedGameplayEffect;
};
