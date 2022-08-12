// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_ApplyCreatureExpressionTag.generated.h"

/**
 * Same as the AnimNotify but it fires and resets after end
 */
UCLASS()
class CREATUREOASIS_API UAnimNotifyState_ApplyCreatureExpressionTag : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, Category = GameplayTag, meta = (ToolTip = "The eye gameplay tag to apply for the notify state"))
	FGameplayTag EyeTag;

	UPROPERTY(EditAnywhere, Category = GameplayTag, meta = (ToolTip = "The mouth gameplay tag to apply for the notify state"))
	FGameplayTag MouthTag;
};
