// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CreatureOasis/Actors/TrackGeneratorActor.h"
#include "UObject/Interface.h"

#include "CreatureRaceTrackInterface.generated.h"

UINTERFACE()
class UCreatureRaceTrackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CREATUREOASIS_API ICreatureRaceTrackInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="CreatureRaceTrackInterface")
	ATrackGeneratorActor* GetActiveTrackGeneratorActor();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="CreatureRaceTrackInterface")
	USplineComponent* GetActiveSplineOfTrackGeneratorActor();

	// For creatures that passed the finish line
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="CreatureRaceTrackInterface")
	void ProcessFinishedCreature(const AActor* FinishedCreatureActor);
};
