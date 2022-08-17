// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_PauseAnimation.h"

UAnimNotify_PauseAnimation::UAnimNotify_PauseAnimation()
	: PauseForSeconds(1.f)
	, PauseForSecondsRandomDeviation(0.f)
{
}

void UAnimNotify_PauseAnimation::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	const float TimerValue = FMath::Max(0.f, FMath::FRandRange(PauseForSeconds - PauseForSecondsRandomDeviation, PauseForSeconds + PauseForSecondsRandomDeviation));

	if (TimerValue <= 0.f)
	{
		return;
	}
	
	//MeshComp->GlobalAnimRateScale = 0.f; // method 1
	//MeshComp->bNoSkeletonUpdate = true; // method 2
	MeshComp->bPauseAnims = true; // method 3
	
	FTimerHandle TimerHandle;
	MeshComp->GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([MeshComp]
	{
		MeshComp->bPauseAnims = false;
	}), TimerValue, false);
}
