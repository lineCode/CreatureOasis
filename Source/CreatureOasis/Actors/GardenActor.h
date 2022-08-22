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
	
	FGameplayTag GetMainTypeTag() const;
	FGameplayTag GetSubTypeTag() const;
	
protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag MainTypeTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag SubTypeTag;
};
