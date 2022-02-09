// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDynamicBTAction.h"

float UBaseDynamicBTAction::CalculateScore_Implementation()
{
	return 0.f;
}

UBehaviorTree* UBaseDynamicBTAction::GetBehaviorTreeToRun_Implementation()
{
	return BehaviorTreeToRun;
}
