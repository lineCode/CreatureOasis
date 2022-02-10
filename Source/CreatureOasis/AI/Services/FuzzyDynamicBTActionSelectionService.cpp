// Fill out your copyright notice in the Description page of Project Settings.

#include "FuzzyDynamicBTActionSelectionService.h"

#include "CreatureOasis/AI/FuzzyLogic/FuzzyLogicInterface.h"
#include "CreatureOasis/AI/FuzzyLogic/Actions/BaseDynamicBTAction.h"

UFuzzyDynamicBTActionSelectionService::UFuzzyDynamicBTActionSelectionService() :
	BestFuzzyAction(nullptr)
{
	NodeName = "Select Action and SetDynamicSubtree";
}

void UFuzzyDynamicBTActionSelectionService::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);

	if (FuzzyActions.Num() <= 0)
	{
		return;
	}
	
	// Calculate best action
	SearchForBestFuzzyAction();

	if (BestFuzzyAction)
	{
		const UBehaviorTree* SubTreeToRun = BestFuzzyAction->GetBehaviorTreeToRun();
		
		if (SubTreeToRun)
		{
			// Inject new Action BT into Dynamic Run task
			SearchData.OwnerComp.SetDynamicSubtree(DynamicBTInjectionTag, BestFuzzyAction->GetBehaviorTreeToRun());
		}
	}
}

void UFuzzyDynamicBTActionSelectionService::SearchForBestFuzzyAction()
{
	float BestScore = 0.f;
	UBaseDynamicBTAction* BestAction = nullptr;
	
	for (const auto Action : FuzzyActions)
	{
		const float CalculatedScore = Action->CalculateScore();

		if (CalculatedScore > BestScore)
		{
			BestScore = CalculatedScore;
			BestAction = Action;
		}
	}

	BestFuzzyAction = BestAction;
}
