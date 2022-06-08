// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "ChaoCoreAttributeSet.h"
#include "GardenActorAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UGardenActorAttributeSet : public UChaoCoreAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Fruit")
	FGameplayAttributeData FruitMaxPortions;
	ATTRIBUTE_ACCESSORS(UGardenActorAttributeSet, FruitMaxPortions);
	
};
