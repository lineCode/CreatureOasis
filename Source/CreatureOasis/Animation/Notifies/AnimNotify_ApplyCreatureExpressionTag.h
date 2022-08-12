// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AnimNotify_ApplyCreatureExpressionTag.generated.h"

/**
 * Same as the AnimNotifyState but it fires and forgets, intended for other elements in game to set a new eye or mouth tag
 */
UCLASS()
class CREATUREOASIS_API UAnimNotify_ApplyCreatureExpressionTag : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, Category = GameplayTag, meta = (ToolTip = "The eye gameplay tag to apply for the notify"))
	FGameplayTag EyeTag;

	UPROPERTY(EditAnywhere, Category = GameplayTag, meta = (ToolTip = "The mouth gameplay tag to apply for the notify"))
	FGameplayTag MouthTag;
};
