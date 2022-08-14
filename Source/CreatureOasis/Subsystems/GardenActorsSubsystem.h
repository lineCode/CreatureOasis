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
	void AddGardenActor(const FGameplayTag GardenActorTypeTag, AActor* GardenActor);

	UFUNCTION(BlueprintCallable, Category="Garden")
	int GetGardenActorCountByTag(const FGameplayTag GameplayTag) const;

	UFUNCTION(BlueprintCallable, Category="Garden")
	bool GetGardenActorsByTag(const FGameplayTag GameplayTag, TArray<AActor*>& OutGardenActors);

	UFUNCTION(BlueprintCallable, Category="Garden")
	bool GetAllGardenActors(TArray<AActor*>& OutGardenActors);
	
	UFUNCTION(BlueprintCallable, Category="Garden")
	AActor* GetClosestGardenActorInRange(const FVector Start, const float Range, const FGameplayTag GardenActorTag);
	
	UFUNCTION(BlueprintCallable, Category="Garden")
	bool GetGardenActorsInRange(const FVector Start, const float Range, const FGameplayTag GardenActorTag, TArray<AActor*>& OutGardenActors);

	UFUNCTION(BlueprintCallable, Category="Garden")
	AActor* GetClosestGardenActorInViewCone(const FVector Start, const FVector Direction, float ConeAngle, const float Range, const FGameplayTag GardenActorTag);

	UFUNCTION(BlueprintCallable, Category="Garden")
	AActor* GetClosestGardenActorInViewConeUsingActor(const AActor* OriginActor, float ConeAngle, const float Range, const FGameplayTag GardenActorTag);

	UFUNCTION(BlueprintCallable, Category="Garden")
	bool HasGardenActorInViewCone(const FVector Start, const FVector Direction, const float ConeAngle, const float Range, const FGameplayTag GardenActorTag);

	UFUNCTION(BlueprintCallable, Category="Garden")
	bool HasGardenActorInViewConeUsingActor(const AActor* OriginActor, const float ConeAngle, const float Range, const FGameplayTag GardenActorTag);

	
	UFUNCTION(BlueprintCallable, Category="Garden")
	bool IsAnyGardenActorOfTypeInRange(const FVector Start, const float Range, const FGameplayTag GardenActorTypeTag);

	UFUNCTION(BlueprintCallable, Category="Garden")
	bool HasGardenActorFromInActorArray(const FGameplayTag GardenActorTypeTag, TArray<AActor*> InActorArray);

	UFUNCTION(BlueprintCallable, Category="Garden")
	AActor* GetClosestGardenActorFromInActorArray(const FVector Start, const FGameplayTag GardenActorTypeTag, const TArray<AActor*> InActorArray);
	
protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
private:
	TMultiMap<FGameplayTag, AActor*> GardenActorsMultiMap;
};
