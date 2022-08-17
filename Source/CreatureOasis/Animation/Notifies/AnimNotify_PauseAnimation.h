// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AnimNotify_PauseAnimation.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UAnimNotify_PauseAnimation : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_PauseAnimation();
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
	UPROPERTY(EditAnywhere)
	float PauseForSeconds;

	UPROPERTY(EditAnywhere)
	float PauseForSecondsRandomDeviation;
};
