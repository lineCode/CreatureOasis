// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SelectStatBasedCreatureAction.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CreatureOasis/Structs/ProjectSettings/GardenSettings.h"

UBTService_SelectStatBasedCreatureAction::UBTService_SelectStatBasedCreatureAction()
{
	NodeName = "";

	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
	
	BooleanBKeyToSet.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_SelectStatBasedCreatureAction, BooleanBKeyToSet));
}

void UBTService_SelectStatBasedCreatureAction::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	const APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (IsValid(OwnerPawn) && OwnerPawn->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		const IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OwnerPawn);
		const UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();
	
		const UGardenSettings* GardenSettings = GetDefault<UGardenSettings>();

		const FCreatureNaturalActionLibraryEntry* MovementModeLibraryEntry = GardenSettings->CreatureNaturalActionLibrary.Find(MovementModeTag);

		if (MovementModeLibraryEntry != nullptr)
		{
			TArray<FGameplayAttribute> OutKeys;
			if (GardenSettings->CreatureStatCalculationLibrary.GetKeys(OutKeys))
			{
				FGameplayAttribute BestAttribute;
				float BestStatCalculationResult = 0.f;
				for (const FGameplayAttribute& Key : OutKeys)
				{
					const FCreatureStatCalculationLibraryEntry* StatCalculationEntry = GardenSettings->CreatureStatCalculationLibrary.Find(Key);
					const float Result = IsValid(StatCalculationEntry->FuzzyActionCalculationObject) ? StatCalculationEntry->FuzzyActionCalculationObject.GetDefaultObject()->CalculateScore(GetWorld(), OwnerComp.GetAIOwner(), AbilitySystemComponent) : StatCalculationEntry->ValToUseWhenComparing;

					if (Result > BestStatCalculationResult)
					{
						BestAttribute = Key;
						BestStatCalculationResult = Result;
					}
				}	

				if (BestAttribute.IsValid() && BestStatCalculationResult != 0.f)
				{
					const FCreatureFuzzyActionStatCollection* ActionStatCollection = MovementModeLibraryEntry->CreatureStatChecks.Find(BestAttribute);

					UBehaviorTree* BestBehaviorTree = nullptr;
					float BestFuzzyActionCalculationResult = 0.f;
					for (const FCreatureFuzzyActionData& FuzzyAction : ActionStatCollection->CreatureFuzzyActionDataArray)
					{
						const float Result = IsValid(FuzzyAction.FuzzyActionCalculationObject) ? FuzzyAction.FuzzyActionCalculationObject.GetDefaultObject()->CalculateScore(GetWorld(), OwnerComp.GetAIOwner(), AbilitySystemComponent) : FuzzyAction.ResultValueToUseOnMissingCalculationObject;
				
						if (Result > BestFuzzyActionCalculationResult)
						{
							BestFuzzyActionCalculationResult = Result;
							BestBehaviorTree = FuzzyAction.BehaviorTreeAction;
						}
					}

					if (BestBehaviorTree != nullptr)
					{
						// Inject new Action BT into Dynamic Run task
						OwnerComp.SetDynamicSubtree(DynamicBTInjectionTag, BestBehaviorTree);

						OwnerComp.GetBlackboardComponent()->SetValueAsBool(BooleanBKeyToSet.SelectedKeyName, true);
					}
					
					return;
				}
			}
		}
	}
	
	OwnerComp.SetDynamicSubtree(DynamicBTInjectionTag, DefaultBTToRun);
}

void UBTService_SelectStatBasedCreatureAction::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
}