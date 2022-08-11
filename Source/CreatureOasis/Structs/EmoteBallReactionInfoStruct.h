#pragma once

#include "AttributeSet.h"

#include "EmoteBallReactionInfoStruct.Generated.h"

USTRUCT(BlueprintType)
struct FEmoteBallReactionInfoStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHideBaseEmoteBall;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMesh* ReactionMesh;
};