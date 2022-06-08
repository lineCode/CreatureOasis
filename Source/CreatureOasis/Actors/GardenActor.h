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

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag GardenActorTypeTag;
};
