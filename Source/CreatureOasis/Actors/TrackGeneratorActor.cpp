// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackGeneratorActor.h"

#include "TrackSegmentActor.h"
#include "Components/SplineComponent.h"
#include "CreatureOasis/Structs/ProjectSettings/TrackSettings.h"

// Sets default values
ATrackGeneratorActor::ATrackGeneratorActor()
	: GeneratedPreviewSegmentCount(0)
	, StartingSegmentTag(FGameplayTag::RequestGameplayTag("Type.TrackSegment.Begin"))
	, RegularSegmentTag(FGameplayTag::RequestGameplayTag("Type.TrackSegment.Regular"))
	, EndingSegmentTag(FGameplayTag::RequestGameplayTag("Type.TrackSegment.End"))
	, bTrackHasEnd(false)
{
	PrimaryActorTick.bCanEverTick = true;

	RoadStartStaticMesh		= LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/CreatureOasis/Art/Meshes/RaceRoads/RaceRoads_Road_Begin.RaceRoads_Road_Begin'"));
	RoadEndStaticMesh		= LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/CreatureOasis/Art/Meshes/RaceRoads/RaceRoads_Road_End.RaceRoads_Road_End'"));
	RoadRegularStaticMesh	= LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/CreatureOasis/Art/Meshes/RaceRoads/RaceRoads_Road_Regular.RaceRoads_Road_Regular'"));
	
	SplineTrack = CreateDefaultSubobject<USplineComponent>(TEXT("SplineTrack"));
	SplineTrack->SetupAttachment(RootComponent);
	
	RootComponent = SplineTrack;

	RootComponent->SetMobility(EComponentMobility::Static);
}

// Called when the game starts or when spawned
void ATrackGeneratorActor::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeSpline();
}

void ATrackGeneratorActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	for (int32 Index = 0; Index < SplineTrack->GetNumberOfSplinePoints(); Index++)
	{
		FVector PointLoc(0.f), PointTangent(0.f);
		SplineTrack->GetLocationAndTangentAtSplinePoint(Index, PointLoc, PointTangent, ESplineCoordinateSpace::World);
		DrawDebugSphere(GetWorld(), PointLoc, 30, 8, FColor::Red, false, -1, 1);
	}
}

void ATrackGeneratorActor::InitializeSpline()
{
	SplineTrack->ClearSplinePoints();
	
	SplineTrack->AddSplineLocalPoint(FVector(0.f));
	
	GenerateSegments(StartingSegmentTag, false);
	GenerateSegments(RegularSegmentTag, false);
}

void ATrackGeneratorActor::GenerateSegments(const FGameplayTag TrackSegmentTag, const bool bIsPreview)
{
	if (!TrackSegmentTag.IsValid() || bTrackHasEnd)
	{
		return;
	}

	const UTrackSettings* TrackSettings = GetDefault<UTrackSettings>();
	if (TrackSettings->TrackSegmentDataMap.Contains(TrackSegmentTag))
	{
		FinalizeCurrentPreviewSegment();
		
		if (HasTrackEnd())
		{
			return;
		}
		
		AddSplinePoint();

		const FTrackSegmentData* TrackSegmentData = TrackSettings->TrackSegmentDataMap.Find(TrackSegmentTag);

		// Now generate mesh
		FVector LastPointLoc(0.f), LastPointTangent(0.f);
		FVector NewPointLoc(0.f), NewPointTangent(0.f);
	
		SplineTrack->GetLocationAndTangentAtSplinePoint(SplineTrack->GetNumberOfSplinePoints() - 2, LastPointLoc, LastPointTangent, ESplineCoordinateSpace::World);
		SplineTrack->GetLocationAndTangentAtSplinePoint(SplineTrack->GetNumberOfSplinePoints() - 1, NewPointLoc, NewPointTangent, ESplineCoordinateSpace::World);

		const FRotator NewSegmentRotation = SplineTrack->GetRotationAtSplinePoint(SplineTrack->GetNumberOfSplinePoints() - 2, ESplineCoordinateSpace::World);
		ATrackSegmentActor* NewSegmentActor = GetWorld()->SpawnActor<ATrackSegmentActor>(TrackSegmentData->TrackSegmentActor->GetDefaultObject()->GetClass(),
			LastPointLoc, NewSegmentRotation);
		
		NewSegmentActor->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
		
		NewSegmentActor->SetStartTangent(LastPointTangent);
		NewSegmentActor->SetEndLocationAndTangent(NewSegmentActor->GetTransform().InverseTransformPosition(NewPointLoc), NewPointTangent);
		NewSegmentActor->SetTrackTagType(TrackSegmentTag);

		if (bIsPreview)
		{
			NewSegmentActor->SetIsBeingPreviewed(true);
			
			GeneratedPreviewSegmentCount++;
		}

		GeneratedTrackSegmentActors.Add(NewSegmentActor);
	}
}

void ATrackGeneratorActor::FinalizeCurrentPreviewSegment()
{
	if (GeneratedTrackSegmentActors.IsEmpty() || GeneratedPreviewSegmentCount <= 0)
	{
		return;
	}
	
	if (GeneratedTrackSegmentActors.Last()->GetTrackTagType() == EndingSegmentTag)
	{
		bTrackHasEnd = true;
	}

	for	(int32 Index = 0; Index < GeneratedPreviewSegmentCount; Index++)
	{
		ATrackSegmentActor* TrackSegmentActor = GeneratedTrackSegmentActors.Last(Index);
		TrackSegmentActor->SetIsBeingPreviewed(false);
	}

	GeneratedPreviewSegmentCount = 0;
}

void ATrackGeneratorActor::AddSplinePoint() const
{
	const int32 NumSplinePoints = SplineTrack->GetNumberOfSplinePoints();
	
	const FRotator PointRotation = SplineTrack->GetRotationAtSplinePoint(NumSplinePoints, ESplineCoordinateSpace::Local);
	const FVector PointLocation = SplineTrack->GetLocationAtSplinePoint(NumSplinePoints, ESplineCoordinateSpace::Local);

	FVector PointDirection = SplineTrack->GetDirectionAtSplinePoint(NumSplinePoints, ESplineCoordinateSpace::Local);
	if (PointDirection.IsZero())
	{
		PointDirection = GetActorForwardVector();
	}
	
	FSplinePoint NewSplinePoint;
	NewSplinePoint.Position = PointLocation + PointDirection * 400.f;
	NewSplinePoint.Rotation = PointRotation;
	NewSplinePoint.Scale = FVector(1.f);
	NewSplinePoint.Type = ESplinePointType::Curve;
	NewSplinePoint.InputKey = static_cast<float>(NumSplinePoints);
	
	SplineTrack->AddPoint(NewSplinePoint);
}

bool ATrackGeneratorActor::RemovePreviewSegments()
{
	if (GeneratedPreviewSegmentCount <= 0)
	{
		return false;
	}
	
	const int32 NumSegmentsToRemove = GeneratedPreviewSegmentCount;
	GeneratedPreviewSegmentCount = 0;

	for	(int32 Index = 0; Index < NumSegmentsToRemove; Index++)
	{
		RemoveSegmentAtEnd();
	}
	
	return true;
}

bool ATrackGeneratorActor::RemoveSegmentAtEnd()
{
	// Remove any segments used for previewing if any exist
	RemovePreviewSegments();
	
	// Dont ever remove the first two segments
	if (SplineTrack->GetNumberOfSplineSegments() <= 2)
	{
		return false;
	}
	
	SplineTrack->RemoveSplinePoint(SplineTrack->GetNumberOfSplinePoints() - 1);
	if (GeneratedTrackSegmentActors.Num() > 0)
	{
		ATrackSegmentActor* TrackSegmentActor = GeneratedTrackSegmentActors[GeneratedTrackSegmentActors.Num() - 1];
		if (IsValid(TrackSegmentActor))
		{
			TrackSegmentActor->Destroy();
		
			GeneratedTrackSegmentActors.RemoveAt(GeneratedTrackSegmentActors.Num() - 1);

			if (bTrackHasEnd)
			{
				bTrackHasEnd = false;
			}

			return true;
		}
	}
	
	
	GeneratedTrackSegmentActors.RemoveAt(GeneratedTrackSegmentActors.Num() - 1);

	return false;
}

bool ATrackGeneratorActor::HasTrackEnd() const
{
	return bTrackHasEnd;
}

void ATrackGeneratorActor::ChangePreviewSegment(const FGameplayTag SegmentTag)
{
	RemovePreviewSegments();

	GenerateSegments(SegmentTag, true);
}

bool ATrackGeneratorActor::GetSpawnPoints(TArray<USceneComponent*>& OutSpawnPoints)
{
	if (!GeneratedTrackSegmentActors.IsEmpty() && GeneratedTrackSegmentActors.IsValidIndex(0))
	{
		TArray<UActorComponent*> ActorComponents = GeneratedTrackSegmentActors[0]->GetComponentsByTag(USceneComponent::StaticClass()
			, TEXT("SpawnPoint"));
		if (!ActorComponents.IsEmpty())
		{
			for (UActorComponent* ActorComponent : ActorComponents)
			{
				OutSpawnPoints.Add(Cast<USceneComponent>(ActorComponent));
			}
			return true;
		}
	}

	return false;
}

void ATrackGeneratorActor::SetPreviewSegmentLength(const float InLength)
{
	if (GeneratedPreviewSegmentCount <= 0)
	{
		return;
	}

	const ATrackSegmentActor* TrackSegmentActor = GeneratedTrackSegmentActors[GeneratedTrackSegmentActors.Num() - 1];
	if (IsValid(TrackSegmentActor) && TrackSegmentActor->GetTrackTagType() == RegularSegmentTag)
	{
		SplineTrack->SetLocationAtSplinePoint(SplineTrack->GetNumberOfSplinePoints() - 1, TrackSegmentActor->GetActorLocation() + TrackSegmentActor->GetActorForwardVector() * InLength, ESplineCoordinateSpace::World);
	
		FVector EndPointLoc(0.f), EndPointTangent(0.f);
		SplineTrack->GetLocationAndTangentAtSplinePoint(SplineTrack->GetNumberOfSplinePoints() - 1, EndPointLoc, EndPointTangent, ESplineCoordinateSpace::World);
	
		TrackSegmentActor->SetEndLocationAndTangent(TrackSegmentActor->GetTransform().InverseTransformPosition(EndPointLoc), EndPointTangent);
	}
}

bool ATrackGeneratorActor::CanSetSegmentLength() const
{
	return false;
}

void ATrackGeneratorActor::SetSegmentWidth(const float InWidth)
{
}

bool ATrackGeneratorActor::CanSetSegmentWidth() const
{
	return false;
}

void ATrackGeneratorActor::SetSegmentElevation(const float InElevation)
{
}

bool ATrackGeneratorActor::CanSetSegmentElevation() const
{
	return false;
}
