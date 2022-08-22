// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAttributeSet.h"
#include "TrackSegmentAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UTrackSegmentAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Attributes|TrackSegment")
	FGameplayAttributeData Length;
	ATTRIBUTE_ACCESSORS(UTrackSegmentAttributeSet, Length);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|TrackSegment")
	FGameplayAttributeData Bank;
	ATTRIBUTE_ACCESSORS(UTrackSegmentAttributeSet, Bank);

	UPROPERTY(BlueprintReadOnly, Category="Attributes|TrackSegment")
	FGameplayAttributeData Width;
	ATTRIBUTE_ACCESSORS(UTrackSegmentAttributeSet, Width);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes|TrackSegment")
	FGameplayAttributeData Elevation;
	ATTRIBUTE_ACCESSORS(UTrackSegmentAttributeSet, Elevation);
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes|TrackSegment")
	FGameplayAttributeData Thickness;
	ATTRIBUTE_ACCESSORS(UTrackSegmentAttributeSet, Thickness);
};
