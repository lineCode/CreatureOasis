// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Containers/Map.h"
#include "GardenActorsManager.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UGardenActorsManager : public UObject
{
	GENERATED_BODY()

	UGardenActorsManager();

public:
	UFUNCTION(BlueprintCallable)
	void AddGardenActor(FGameplayTag GardenActorTypeTag, AActor* GardenActor);

	UFUNCTION(BlueprintCallable)
	int GetGardenActorCountByTag(FGameplayTag GameplayTag) const;

	UFUNCTION(BlueprintCallable)
	bool GetGardenActorsByTag(FGameplayTag GameplayTag, TArray<AActor*>& OutGardenActors);
	
private:
	TMultiMap<FGameplayTag, AActor*> GardenActorsMultiMap;
};
