#pragma once

#include "GameplayTagContainer.h"
#include "CreatureOasis/Structs/TrackSegmentData.h"

#include "TrackSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, defaultconfig, meta = (DisplayName="Track Settings"))
class UTrackSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Track")
	TMap<FGameplayTag, FTrackSegmentData> TrackSegmentDataMap;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Track")
	TArray<FGameplayTag> TrackSegmentTagArray;
};