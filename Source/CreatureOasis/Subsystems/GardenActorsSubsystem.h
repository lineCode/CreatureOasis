// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GardenActorsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UGardenActorsSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Garden")
	void AddGardenActor(FGameplayTag GardenActorTypeTag, AActor* GardenActor);

	UFUNCTION(BlueprintCallable, Category="Garden")
	int GetGardenActorCountByTag(FGameplayTag GameplayTag) const;

	UFUNCTION(BlueprintCallable, Category="Garden")
	bool GetGardenActorsByTag(FGameplayTag GameplayTag, TArray<AActor*>& OutGardenActors);

	UFUNCTION(BlueprintCallable, Category="Garden")
	bool GetAllGardenActors(TArray<AActor*>& OutGardenActors);
	
	UFUNCTION(BlueprintCallable, Category="Garden")
	AActor* GetClosestGardenActorInRange(FVector Start, const float Range, FGameplayTag GardenActorTag);
	
	UFUNCTION(BlueprintCallable, Category="Garden")
	bool GetGardenActorsInRange(FVector Start, const float Range, FGameplayTag GardenActorTag, TArray<AActor*>& OutGardenActors);

	UFUNCTION(BlueprintCallable, Category="Garden")
	bool IsAnyGardenActorOfTypeInRange(FVector Start, const float Range, FGameplayTag GardenActorTypeTag);
	
protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
private:
	TMultiMap<FGameplayTag, AActor*> GardenActorsMultiMap;
};
