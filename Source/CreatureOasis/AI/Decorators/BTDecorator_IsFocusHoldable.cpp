// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsFocusHoldable.h"

#include "AIController.h"
#include "CreatureOasis/Components/HoldableAnchorComponent.h"

UBTDecorator_IsFocusHoldable::UBTDecorator_IsFocusHoldable()
{
	NodeName = TEXT("IsFocusHoldable");
}

bool UBTDecorator_IsFocusHoldable::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	const AAIController* AIController = OwnerComp.GetAIOwner();
	const AActor* AvatarOwner = AIController->GetPawn();
	const UHoldableAnchorComponent* HoldableAnchorComponent = AvatarOwner->FindComponentByClass<UHoldableAnchorComponent>();

	if (!IsValid(HoldableAnchorComponent))
	{
		return false;
	}
	
	const AActor* FocusActor = OwnerComp.GetAIOwner()->GetFocusActor();
	const AActor* DetectedHoldableActor = HoldableAnchorComponent->DetectHoldableActor();
	
	return FocusActor == DetectedHoldableActor;
}
