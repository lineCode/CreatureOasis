// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_RandomChance.h"

UBTDecorator_RandomChance::UBTDecorator_RandomChance()
	: RandomChance(0.5f)
{
	NodeName = "Random Chance";
}

bool UBTDecorator_RandomChance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return !(RandomChance <= 0.f) && RandomChance >= FMath::FRandRange(0.0f, 1.0f);
}
