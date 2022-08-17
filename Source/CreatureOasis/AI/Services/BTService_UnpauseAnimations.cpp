// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UnpauseAnimations.h"

#include "AIController.h"
#include "GameFramework/Character.h"

UBTService_UnpauseAnimations::UBTService_UnpauseAnimations()
{
	bNotifyBecomeRelevant = true;
	bNotifyTick = false;
}

void UBTService_UnpauseAnimations::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	if (!IsValid(OwnerComp.GetAIOwner()) || !IsValid(OwnerComp.GetAIOwner()->GetCharacter()))
	{
		return;
	}
	
	USkeletalMeshComponent* SkeletalMeshComponent = OwnerComp.GetAIOwner()->GetCharacter()->GetMesh();
	if (SkeletalMeshComponent->bPauseAnims)
	{
		SkeletalMeshComponent->bPauseAnims = false;
	}
}