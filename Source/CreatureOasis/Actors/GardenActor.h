// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "CreatureOasis/GameplayAbilitySystem/GASActor.h"

#include "GardenActor.generated.h"

UCLASS()
class CREATUREOASIS_API AGardenActor : public AGASActor
{
	GENERATED_BODY()

public:
	AGardenActor();

	void InitializeFromSaveGame(const FGameplayTag InMainTypeTag, const FGameplayTag InSubTypeTag);

	UFUNCTION(BlueprintCallable)
	FGameplayTag GetMainTypeTag() const;

	UFUNCTION(BlueprintCallable)
	FGameplayTag GetSubTypeTag() const;

	UFUNCTION(BlueprintCallable)
	void SetSubTypeTag(const FGameplayTag InTag);
	
protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag MainTypeTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag SubTypeTag;
};
