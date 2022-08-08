﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "FuzzyDynamicBTActionSelectionService.h"

#include "AIController.h"
#include "CreatureOasis/AI/FuzzyLogic/FuzzyLogicInterface.h"
#include "CreatureOasis/AI/FuzzyLogic/Actions/BaseDynamicBTAction.h"
#include "CreatureOasis/GameplayAbilitySystem/BaseAbilitySystemComponent.h"
#include "CreatureOasis/GameplayAbilitySystem/GASCharacter.h"

UFuzzyDynamicBTActionSelectionService::UFuzzyDynamicBTActionSelectionService()
{
	NodeName = "Select Fuzzy Action and SetDynamicSubtree";

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

	UBaseDynamicBTAction* BestFuzzyAction = SearchForBestFuzzyAction(OwnerComp);;

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

UBaseDynamicBTAction* UFuzzyDynamicBTActionSelectionService::SearchForBestFuzzyAction(const UBehaviorTreeComponent& OwnerComp)
{
	float BestScore = 0.f;
	UBaseDynamicBTAction* BestAction = nullptr;
	AAIController* AIController = OwnerComp.GetAIOwner();
	
	for (const TSubclassOf<UBaseDynamicBTAction> Action : FuzzyActions)
	{
		const UBaseAbilitySystemComponent* AbilitySystemComponent = static_cast<UBaseAbilitySystemComponent*>(
			static_cast<AGASCharacter*>(AIController->GetCharacter())->GetAbilitySystemComponent());
		
		const float CalculatedScore = IFuzzyLogicInterface::Execute_CalculateScore(Action.GetDefaultObject(), GetWorld(), AIController, AbilitySystemComponent);
		
		if (CalculatedScore > BestScore)
		{
			BestScore = CalculatedScore;
			BestAction = Action.GetDefaultObject();
		}
	}

	return BestAction;
}
