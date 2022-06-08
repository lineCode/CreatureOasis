// Fill out your copyright notice in the Description page of Project Settings.


#include "GardenActorsManager.h"

UGardenActorsManager::UGardenActorsManager()
	: GardenActorsMultiMap()
{
}

void UGardenActorsManager::AddGardenActor(FGameplayTag GardenActorTypeTag, AActor* GardenActor)
{
	GardenActorsMultiMap.Add(GardenActorTypeTag, GardenActor);
}

int UGardenActorsManager::GetGardenActorCountByTag(FGameplayTag GameplayTag) const
{
	if (GardenActorsMultiMap.IsEmpty())
	{
		return 0;
	}
	
	TArray<AActor*> FoundActors;
	GardenActorsMultiMap.MultiFind(GameplayTag, FoundActors);
	return FoundActors.Num();
}

bool UGardenActorsManager::GetGardenActorsByTag(FGameplayTag GameplayTag, TArray<AActor*>& OutGardenActors)
{
	if (GardenActorsMultiMap.IsEmpty())
	{
		return false;
	}

	OutGardenActors.Empty();
	
	GardenActorsMultiMap.MultiFind(GameplayTag, OutGardenActors);
	
	return !OutGardenActors.IsEmpty();
}
