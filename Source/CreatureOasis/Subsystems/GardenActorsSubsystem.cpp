// Fill out your copyright notice in the Description page of Project Settings.


#include "GardenActorsSubsystem.h"

void UGardenActorsSubsystem::AddGardenActor(FGameplayTag GardenActorTypeTag, AActor* GardenActor)
{
	GardenActorsMultiMap.Add(GardenActorTypeTag, GardenActor);
}

int UGardenActorsSubsystem::GetGardenActorCountByTag(FGameplayTag GameplayTag) const
{
	if (GardenActorsMultiMap.IsEmpty())
	{
		return 0;
	}
	
	TArray<AActor*> FoundActors;
	GardenActorsMultiMap.MultiFind(GameplayTag, FoundActors);
	return FoundActors.Num();
}

bool UGardenActorsSubsystem::GetGardenActorsByTag(FGameplayTag GameplayTag, TArray<AActor*>& OutGardenActors)
{
	if (GardenActorsMultiMap.IsEmpty())
	{
		return false;
	}

	OutGardenActors.Empty();
	
	GardenActorsMultiMap.MultiFind(GameplayTag, OutGardenActors);
	
	return !OutGardenActors.IsEmpty();
}

void UGardenActorsSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
}

AActor* UGardenActorsSubsystem::GetClosestGardenActorInRange(FVector Start,
	const float Range, FGameplayTag GardenActorTag)
{
	TArray<AActor*> GardenActors;
	GetGardenActorsByTag(GardenActorTag, GardenActors);

	TPair<float, AActor*> ClosestActor(TNumericLimits<float>::Max(), nullptr);
	for (AActor* Actor : GardenActors)
	{
		const float Distance = FVector::Distance(Start, Actor->GetActorLocation());
		if (Distance < Range && Distance < ClosestActor.Key)
		{
			ClosestActor.Key = Distance;
			ClosestActor.Value = Actor;
		}
	}

	return ClosestActor.Value;
}

bool UGardenActorsSubsystem::GetGardenActorsInRange(FVector Start,
															const float Range, FGameplayTag GardenActorTag, TArray<AActor*>& OutGardenActors)
{
	TArray<AActor*> GardenActors;
	GetGardenActorsByTag(GardenActorTag, GardenActors);
	for (AActor* Actor : GardenActors)
	{
		const float Distance = FVector::Distance(Start, Actor->GetActorLocation());
		if (Distance < Range)
		{
			OutGardenActors.Add(Actor);
		}
	}

	return !OutGardenActors.IsEmpty();
}

bool UGardenActorsSubsystem::IsAnyGardenActorOfTypeInRange(FVector Start,
	const float Range, FGameplayTag GardenActorTypeTag)
{
	TArray<AActor*> GardenActors;
	if (GetGardenActorsByTag(GardenActorTypeTag, GardenActors))
	{
		for (const AActor* Actor : GardenActors)
		{
			const float Distance = FVector::Distance(Start, Actor->GetActorLocation());
			if (Distance < Range)
			{
				return true;
			}
		}
	}

	return false;
}