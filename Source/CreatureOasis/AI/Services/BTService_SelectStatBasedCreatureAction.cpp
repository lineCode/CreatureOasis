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
					UE_LOG(LogTemp, Warning, TEXT("[FuzzyAction] Checking key: %s Result: %i"), *Key.AttributeName, (int)(StatCalculationEntry != nullptr));

					if (Key.IsValid() && StatCalculationEntry != nullptr && AbilitySystemComponent->GetNumericAttribute(Key) > StatCalculationEntry->AttributeMinValue)
					{

						if (!(StatCalculationEntry->ChanceToApply <= 0.f) && StatCalculationEntry->ChanceToApply >= FMath::FRandRange(0.0f, 1.0f))
						{
							const float Result = (!StatCalculationEntry->bUseCustomValues && IsValid(StatCalculationEntry->FuzzyActionCalculationObject)) ? StatCalculationEntry->FuzzyActionCalculationObject.GetDefaultObject()->CalculateScore(GetWorld(), OwnerComp.GetAIOwner(), AbilitySystemComponent) : StatCalculationEntry->GetCustomResultValue();

							if (Result > BestStatCalculationResult)
							{
								BestAttribute = Key;
								BestStatCalculationResult = Result;
							}
						}
					}
				}	

				if (BestAttribute.IsValid() && BestStatCalculationResult != 0.f)
				{
					UE_LOG(LogTemp, Warning, TEXT("[FuzzyAction] BestAttribute found: %s %f"), *BestAttribute.AttributeName, BestStatCalculationResult);

					const FCreatureFuzzyActionStatCollection* ActionStatCollection = MovementModeLibraryEntry->CreatureStatChecks.Find(BestAttribute);

					UBehaviorTree* BestBehaviorTree = nullptr;
					float BestFuzzyActionCalculationResult = 0.f;
					for (const FCreatureFuzzyActionData& FuzzyAction : ActionStatCollection->CreatureFuzzyActionDataArray)
					{
						if (AbilitySystemComponent->GetNumericAttribute(BestAttribute) > FuzzyAction.AttributeMinValue)
						{
							if (!(FuzzyAction.ChanceToApply <= 0.f) && FuzzyAction.ChanceToApply >= FMath::FRandRange(0.0f, 1.0f))
							{
								const float Result = (!FuzzyAction.bUseCustomValues && IsValid(FuzzyAction.FuzzyActionCalculationObject)) ? FuzzyAction.FuzzyActionCalculationObject.GetDefaultObject()->CalculateScore(GetWorld(), OwnerComp.GetAIOwner(), AbilitySystemComponent) : FuzzyAction.GetCustomResultValue();
						
								if (Result > BestFuzzyActionCalculationResult)
								{
									BestFuzzyActionCalculationResult = Result;
									BestBehaviorTree = FuzzyAction.BehaviorTreeAction;
								}
							}
						}
					}

					if (BestBehaviorTree != nullptr)
					{
						UE_LOG(LogTemp, Warning, TEXT("[FuzzyActions] Best action found: %s %f"), *BestBehaviorTree->GetName(), BestFuzzyActionCalculationResult);
						
						// Inject new Action BT into Dynamic Run task
						OwnerComp.SetDynamicSubtree(DynamicBTInjectionTag, BestBehaviorTree);

						OwnerComp.GetBlackboardComponent()->SetValueAsBool(BooleanBKeyToSet.SelectedKeyName, true);
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("[FuzzyActions] No action found"));
						OwnerComp.SetDynamicSubtree(DynamicBTInjectionTag, DefaultBTToRun);
					}
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("[FuzzyActions] No action found"));
					OwnerComp.SetDynamicSubtree(DynamicBTInjectionTag, DefaultBTToRun);
				}
			}
		}
	}
}

void UBTService_SelectStatBasedCreatureAction::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
}