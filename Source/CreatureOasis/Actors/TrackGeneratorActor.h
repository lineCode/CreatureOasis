// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "TrackSegmentActor.h"
#include "GameFramework/Actor.h"

#include "TrackGeneratorActor.generated.h"

class USplineComponent;

UCLASS()
class CREATUREOASIS_API ATrackGeneratorActor : public AActor
{
	GENERATED_BODY()

public:
	ATrackGeneratorActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void InitializeSpline();

	UFUNCTION(BlueprintCallable)
	void GenerateSegments(const FGameplayTag TrackSegmentTag, const bool bIsPreview = false);
	
	UFUNCTION(BlueprintCallable)
	void FinalizeCurrentPreviewSegment();
	
	UFUNCTION()
	void AddSplinePoint() const;

	UFUNCTION()
	bool RemovePreviewSegments();

	UFUNCTION(BlueprintCallable)
	bool RemoveSegmentAtEnd();

	UFUNCTION(BlueprintCallable)
	bool HasTrackEnd() const;
	
	UFUNCTION(BlueprintCallable)
	void ChangePreviewSegment(const FGameplayTag SegmentTag);

	UFUNCTION(BlueprintCallable)
	const USplineComponent* GetSplineComponent() const;

	UFUNCTION(BlueprintCallable)
	void GenerateCollision();
	
	// Returns false if no spawn points were found
	UFUNCTION(BlueprintCallable)
	bool GetSpawnPoints(TArray<USceneComponent*>& OutSpawnPoints);
	
	UFUNCTION(BlueprintCallable, Category="PreviewSegmentTools")
	void SetPreviewSegmentLength(const float InLength);

	UFUNCTION(BlueprintCallable, Category="PreviewSegmentTools")
	bool CanSetSegmentLength() const;
	
	UFUNCTION(BlueprintCallable, Category="PreviewSegmentTools")
	void SetSegmentWidth(const float InWidth);

	UFUNCTION(BlueprintCallable, Category="PreviewSegmentTools")
	bool CanSetSegmentWidth() const;

	UFUNCTION(BlueprintCallable, Category="PreviewSegmentTools")
	void SetSegmentElevation(const float InElevation);

	UFUNCTION(BlueprintCallable, Category="PreviewSegmentTools")
	bool CanSetSegmentElevation() const;

	UFUNCTION(BlueprintCallable, Category="PreviewSegmentTools")
	void SetSegmentRotation(const FRotator& InRotation);
	
	// Preview segment data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayTag CurrentPreviewSegmentTag;
	
	int32 GeneratedPreviewSegmentCount;

	// Type segment tags the generated uses internally
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag StartingSegmentTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag RegularSegmentTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag EndingSegmentTag;

	// Track debug meshes
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* RoadStartStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* RoadRegularStaticMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* RoadEndStaticMesh;
	
	// Bulk of data
	UPROPERTY()
	USplineComponent* SplineTrack;

	UPROPERTY()
	TArray<ATrackSegmentActor*> GeneratedTrackSegmentActors;

	bool bTrackHasEnd;
};
