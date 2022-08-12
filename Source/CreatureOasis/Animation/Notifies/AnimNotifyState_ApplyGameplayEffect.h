// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_ApplyGameplayEffect.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UAnimNotifyState_ApplyGameplayEffect : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, Category = GameplayEffect, meta = (ToolTip = "The gameplay effect to apply for the notify state"))
	TSubclassOf<UGameplayEffect> GameplayEffectToApply;
};
