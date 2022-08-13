// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_ClearBlackboardKey.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTService_ClearBlackboardKey::UBTService_ClearBlackboardKey()
	: bClearOnBecomeRelevant(false)
	, bClearOnCeaseRelevant(false)
{
	NodeName = "Clear BlackboardKey";
	
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}

void UBTService_ClearBlackboardKey::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	if (bClearOnBecomeRelevant)
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}

void UBTService_ClearBlackboardKey::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);

	if (bClearOnCeaseRelevant)
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}
