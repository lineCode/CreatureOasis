// Fill out your copyright notice in the Description page of Project Settings.


#include "GardenStaticsBlueprintLibrary.h"

#include "CreatureOasis/GameModes/BaseGardenGameMode.h"
#include "CreatureOasis/Objects/GardenActorsManager.h"

ABaseGardenGameMode* UGardenStaticsBlueprintLibrary::GetGardenGameMode(const UObject* WorldContextObject)
{
	const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	return Cast<ABaseGardenGameMode>(World->GetAuthGameMode());
}

UGardenActorsManager* UGardenStaticsBlueprintLibrary::GetGardenActorsManager(const UObject* WorldContextObject)
{
	return GetGardenGameMode(WorldContextObject)->GetGardenActorsManager();
}

AActor* UGardenStaticsBlueprintLibrary::GetClosestGardenActorInRange(const UObject* WorldContextObject, FVector Start,
	const float Range, FGameplayTag GardenActorTag)
{
	TArray<AActor*> GardenActors;
	GetGardenActorsManager(WorldContextObject)->GetGardenActorsByTag(GardenActorTag, GardenActors);

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

bool UGardenStaticsBlueprintLibrary::GetGardenActorsInRange(const UObject* WorldContextObject, FVector Start,
                                                            const float Range, FGameplayTag GardenActorTag, TArray<AActor*>& OutGardenActors)
{
	TArray<AActor*> GardenActors;
	GetGardenActorsManager(WorldContextObject)->GetGardenActorsByTag(GardenActorTag, GardenActors);
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

bool UGardenStaticsBlueprintLibrary::IsGardenActorInRange(const UObject* WorldContextObject, FVector Start,
	const float Range, FGameplayTag GardenActorTag)
{
	TArray<AActor*> GardenActors;
	if (GetGardenActorsManager(WorldContextObject)->GetGardenActorsByTag(GardenActorTag, GardenActors))
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
