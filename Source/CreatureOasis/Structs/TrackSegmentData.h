#pragma once
#include "CreatureOasis/Actors/TrackSegmentActor.h"

#include "TrackSegmentData.Generated.h"

USTRUCT(BlueprintType)
struct FTrackSegmentData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ATrackSegmentActor> TrackSegmentActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ExtraTracksFront = 0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ExtraTracksBack = 0.f;
};