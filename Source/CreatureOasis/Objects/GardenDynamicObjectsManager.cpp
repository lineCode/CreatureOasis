// Fill out your copyright notice in the Description page of Project Settings.


#include "GardenDynamicObjectsManager.h"

#include "Kismet/GameplayStatics.h"

UGardenDynamicObjectsManager::UGardenDynamicObjectsManager()
	: FruitCount(0)
{
}

void UGardenDynamicObjectsManager::Initialize()
{
	
}

void UGardenDynamicObjectsManager::Uninitialize()
{
	FruitCount = 0;
}

void UGardenDynamicObjectsManager::IncrementFruitCount()
{
	FruitCount++;
}

void UGardenDynamicObjectsManager::DecrementFruitCount()
{
	FruitCount--;
}

int UGardenDynamicObjectsManager::GetFruitCount() const
{
	return FruitCount;
}