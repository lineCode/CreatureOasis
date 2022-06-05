// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "FruitTableRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CREATUREOASIS_API FFruitTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="FruitRowBase")
	FGameplayTag GameplayTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="FruitRowBase")
	UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="FruitRowBase")
	FVector MeshScaleOverride = FVector(1.f);
	
	// The amount of "bites" a creature can take from this fruit
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="FruitStats")
	int32 MaxPortions = 4;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="FruitGameplayEffects")
	TSubclassOf<UGameplayEffect> PerBiteGameplayEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="FruitGameplayEffects")
	TSubclassOf<UGameplayEffect> OnDepletedGameplayEffect;
};
