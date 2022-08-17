// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ApplyCreatureExpressionGameplayTagsWhileRelevant.h"

#include "AIController.h"
#include "CreatureOasis/Interfaces/CreatureComponentGetterInterface.h"

UBTService_ApplyCreatureExpressionGameplayTagsWhileRelevant::UBTService_ApplyCreatureExpressionGameplayTagsWhileRelevant()
	: EyeTag(FGameplayTag::EmptyTag)
	, MouthTag(FGameplayTag::EmptyTag)
	, bClearEyesOnEmptyTag(false)
	, bClearMouthOnEmptyTag(false)
{
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}

void UBTService_ApplyCreatureExpressionGameplayTagsWhileRelevant::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (IsValid(OwnerPawn) && OwnerPawn->GetClass()->ImplementsInterface(UCreatureComponentGetterInterface::StaticClass()))
	{
		if (UCreatureExpressionComponent* CreatureExpressionComp = ICreatureComponentGetterInterface::Execute_GetCreatureExpressionComponent(OwnerPawn))
		{
			if (bUseContainers)
			{
				if (EyeTagContainer.IsValid())
				{
					CreatureExpressionComp->SetRandomEyeTag(EyeTagContainer);
				}
			
				if (MouthTagContainer.IsValid())
				{
					CreatureExpressionComp->SetRandomMouthTag(MouthTagContainer);
				}
			}
			else
			{
				if (EyeTag.IsValid())
				{
					CreatureExpressionComp->SetEyeTag(EyeTag);
				}
			
				if (MouthTag.IsValid())
				{
					CreatureExpressionComp->SetMouthTag(MouthTag);
				}
			}

			if (bClearEyesOnEmptyTag)
			{
				CreatureExpressionComp->ClearEyeTag();
			}

			if (bClearMouthOnEmptyTag)
			{
				CreatureExpressionComp->ClearMouthTag();
			}
		}
	}
}

void UBTService_ApplyCreatureExpressionGameplayTagsWhileRelevant::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);

	if (!bResetExpressionOnCeaseRelevant)
	{
		return;
	}
	
	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (IsValid(OwnerPawn) && OwnerPawn->GetClass()->ImplementsInterface(UCreatureComponentGetterInterface::StaticClass()))
	{
		if (UCreatureExpressionComponent* CreatureExpressionComp = ICreatureComponentGetterInterface::Execute_GetCreatureExpressionComponent(OwnerPawn); IsValid(CreatureExpressionComp))
		{
			CreatureExpressionComp->ClearEyeTag();
			CreatureExpressionComp->ClearMouthTag();
		}
	}
}
