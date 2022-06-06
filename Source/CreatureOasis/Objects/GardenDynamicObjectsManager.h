// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GardenDynamicObjectsManager.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UGardenDynamicObjectsManager : public UObject
{
	GENERATED_BODY()

	UGardenDynamicObjectsManager();

public:
	void Initialize();
	void Uninitialize();

	UFUNCTION(BlueprintCallable)
	void IncrementFruitCount();
	UFUNCTION(BlueprintCallable)
	void DecrementFruitCount();

	int GetFruitCount() const;
	
private:
	int FruitCount;
};
