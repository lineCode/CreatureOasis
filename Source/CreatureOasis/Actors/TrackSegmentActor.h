// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "CreatureOasis/GameplayAbilitySystem/GASActor.h"

#include "TrackSegmentActor.generated.h"

class USplineMeshComponent;

UCLASS()
class CREATUREOASIS_API ATrackSegmentActor : public AGASActor
{
	GENERATED_BODY()

public:
	ATrackSegmentActor();

	void SetStartTangent(const FVector NewStartTangent) const;
	void SetEndLocationAndTangent(const FVector NewEndLoc, const FVector NewEndTangent) const;

	void SetTrackTagType(const FGameplayTag TagType);
	FGameplayTag GetTrackTagType() const;

	void SetIsBeingPreviewed(const bool bInIsBeingPreviewed);
	bool GetIsBeingPreviewed() const;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* FallBackTrackMesh;
	
	UPROPERTY()
	USplineMeshComponent* SplineMeshComponent;

	UPROPERTY()
	UMaterial* PreviewMaterial;

	UPROPERTY()
	UMaterialInterface* DefaultMaterial;
	
	FGameplayTag TrackTagType;

	bool bIsBeingPreviewed;
};
