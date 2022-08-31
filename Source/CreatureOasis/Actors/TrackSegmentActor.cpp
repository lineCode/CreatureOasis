﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "TrackSegmentActor.h"

#include "AbilitySystemComponent.h"
#include "Components/SplineMeshComponent.h"
#include "CreatureOasis/GameplayAbilitySystem/AttributeSets/TrackSegmentAttributeSet.h"

// Sets default values
ATrackSegmentActor::ATrackSegmentActor()
	: bIsBeingPreviewed(false)
{
	PrimaryActorTick.bCanEverTick = true;

	FallBackTrackMesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/CreatureOasis/Art/Meshes/RaceRoads/RaceRoads_Road_Regular.RaceRoads_Road_Regular'"));
	PreviewMaterial = LoadObject<UMaterial>(nullptr, TEXT("Material'/Game/CreatureOasis/Art/Characters/Chao/Materials/EmoteBall/M_EmoteBallThrob.M_EmoteBallThrob'"));
	
	FAttributeDefaults AttributeDefaults;
	AttributeDefaults.Attributes = UTrackSegmentAttributeSet::StaticClass();
	AttributeDefaults.DefaultStartingTable = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/CreatureOasis/DataTables/DT_TrackStartingAttributes.DT_TrackStartingAttributes'"));
	AbilitySystemComponent->DefaultStartingData.Add(AttributeDefaults);
	
	SplineMeshComponent = CreateDefaultSubobject<USplineMeshComponent>(TEXT("SplineMeshComponent"));
	SplineMeshComponent->SetupAttachment(RootComponent);
	SplineMeshComponent->SetStaticMesh(FallBackTrackMesh);
	SplineMeshComponent->SetEndPosition(GetActorForwardVector() * 400.f);
	
	SplineMeshComponent->SetStartScale(FVector2D(2.f, 1.f));
	SplineMeshComponent->SetEndScale(FVector2D(2.f, 1.f));
}

void ATrackSegmentActor::SetStartTangent(const FVector NewStartTangent) const
{
	SplineMeshComponent->SetStartTangent(NewStartTangent);
}

void ATrackSegmentActor::SetEndLocationAndTangent(const FVector NewEndLoc, const FVector NewEndTangent) const
{
	SplineMeshComponent->SetEndPosition(NewEndLoc);
	SplineMeshComponent->SetEndTangent(NewEndTangent);
}

void ATrackSegmentActor::SetTrackTagType(const FGameplayTag TagType)
{
	TrackTagType = TagType;
}

FGameplayTag ATrackSegmentActor::GetTrackTagType() const
{
	return TrackTagType;
}

void ATrackSegmentActor::SetIsBeingPreviewed(const bool bInIsBeingPreviewed)
{
	bIsBeingPreviewed = bInIsBeingPreviewed;

	if (bIsBeingPreviewed)
	{
		SplineMeshComponent->SetMaterial(0, PreviewMaterial);
	}
	else
	{
		SplineMeshComponent->SetMaterial(0, DefaultMaterial);
	}
}

bool ATrackSegmentActor::GetIsBeingPreviewed() const
{
	return bIsBeingPreviewed;
}

void ATrackSegmentActor::SetIsSplineMeshCollisionEnabled(const bool bIsEnabled) const
{
	SplineMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ATrackSegmentActor::SetWidth(const float InWidth) const
{
	SplineMeshComponent->SetStartScale(FVector2D(InWidth, 1.f));
	SplineMeshComponent->SetEndScale(FVector2D(InWidth, 1.f));
}

void ATrackSegmentActor::SetElevation(const float InElevation) const
{
	const FVector2D DefaultScale = SplineMeshComponent->GetEndScale();
	SplineMeshComponent->SetEndScale(FVector2D(DefaultScale.X, InElevation));
}

// Called when the game starts or when spawned
void ATrackSegmentActor::BeginPlay()
{
	Super::BeginPlay();
	
	DefaultMaterial = SplineMeshComponent->GetMaterial(0);
}

// Called every frame
void ATrackSegmentActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
