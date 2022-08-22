// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindNextLocationOnActiveTrackGenerator.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SplineComponent.h"
#include "CreatureOasis/Interfaces/CreatureRaceTrackInterface.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

UBTTask_FindNextLocationOnActiveTrackGenerator::UBTTask_FindNextLocationOnActiveTrackGenerator()
{
	NodeName = TEXT("FindNextLocationOnActiveTrackGenerator");

	bNotifyTick = false;

	// accept only actors and vectors
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindNextLocationOnActiveTrackGenerator, BlackboardKey));
}

EBTNodeResult::Type UBTTask_FindNextLocationOnActiveTrackGenerator::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());

	const USplineComponent* SplineComponent = ICreatureRaceTrackInterface::Execute_GetActiveSplineOfTrackGeneratorActor(GameMode);

	const APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();

	float Result = SplineComponent->FindInputKeyClosestToWorldLocation(OwnerPawn->GetActorLocation());
	const FVector TargetLocation = SplineComponent->GetLocationAtSplineInputKey(Result + 1.f, ESplineCoordinateSpace::World);
	
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, TargetLocation);
	
	return EBTNodeResult::Succeeded;
}
