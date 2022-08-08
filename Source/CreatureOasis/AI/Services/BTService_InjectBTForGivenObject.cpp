// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_InjectBTForGivenObject.h"

#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "CreatureOasis/Interfaces/HoldableAnchorInterface.h"

UBTService_InjectBTForGivenObject::UBTService_InjectBTForGivenObject()
{
	NodeName = "Inject BT for given object type tag";
	
	bNotifyBecomeRelevant = true;
}

void UBTService_InjectBTForGivenObject::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	if (PossibleTreeArray.IsEmpty())
	{
		return;
	}
	
	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (OwnerPawn->GetClass()->ImplementsInterface(UHoldableAnchorInterface::StaticClass()))
	{
		const FGameplayTag ObjectTypeTag = IHoldableAnchorInterface::Execute_GetTypeOfActorBeingHeld(OwnerPawn);
		
		for (FTreeTagElement& TreeTagElement : PossibleTreeArray)
		{
			if (ObjectTypeTag.MatchesAny(TreeTagElement.TagContainer))
			{
				UBehaviorTree* ResultBT = TreeTagElement.BehaviorTree;
				if (IsValid(ResultBT))
				{
					OwnerComp.SetDynamicSubtree(DynamicBTInjectionTag, ResultBT);
					return;
				}
			}
		}
	}
}
