// Fill out your copyright notice in the Description page of Project Settings.

#include "FuzzyDynamicBTActionSelectionService.h"

#include "CreatureOasis/AI/FuzzyLogic/FuzzyLogicInterface.h"
#include "CreatureOasis/AI/FuzzyLogic/Actions/BaseDynamicBTAction.h"

UFuzzyDynamicBTActionSelectionService::UFuzzyDynamicBTActionSelectionService() :
	BestFuzzyAction(nullptr)
{
	NodeName = "Select Action and SetDynamicSubtree";

	bNotifyBecomeRelevant = true;
}

void UFuzzyDynamicBTActionSelectionService::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	UE_LOG(LogTemp, Warning, TEXT("Relevant"));
	
	if (FuzzyActions.Num() <= 0)
	{
		return;
	}
	
	// Calculate best action
	SearchForBestFuzzyAction();

	if (BestFuzzyAction)
	{
		UBehaviorTree* SubTreeToRun = IFuzzyLogicInterface::Execute_GetBehaviorTreeToRun(BestFuzzyAction);
		
		if (SubTreeToRun)
		{
			// Inject new Action BT into Dynamic Run task
			OwnerComp.SetDynamicSubtree(DynamicBTInjectionTag, SubTreeToRun);
		}
	}
}

void UFuzzyDynamicBTActionSelectionService::SearchForBestFuzzyAction()
{
	float BestScore = 0.f;
	UBaseDynamicBTAction* BestAction = nullptr;
	
	for (const TSubclassOf<UBaseDynamicBTAction> Action : FuzzyActions)
	{
		const float CalculatedScore = IFuzzyLogicInterface::Execute_CalculateScore(Action.GetDefaultObject());
		
		if (CalculatedScore > BestScore)
		{
			BestScore = CalculatedScore;
			BestAction = Action.GetDefaultObject();
		}
	}

	BestFuzzyAction = BestAction;
}
