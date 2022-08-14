// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetBoolBlackboardKey.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTService_SetBoolBlackboardKey::UBTService_SetBoolBlackboardKey()
{
	NodeName = "Set Bool BlackboardKey";
	
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
	
	BlackboardKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_SetBoolBlackboardKey, BlackboardKey));
}

void UBTService_SetBoolBlackboardKey::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	if (bSetOnBecomeRelevant)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
	}
}

void UBTService_SetBoolBlackboardKey::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);

	if (bSetOnCeaseRelevant)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
	}
}
