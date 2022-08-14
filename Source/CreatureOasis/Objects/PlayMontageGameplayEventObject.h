// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "UObject/Object.h"
#include "PlayMontageGameplayEventObject.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class CREATUREOASIS_API UPlayMontageGameplayEventObject : public UObject
{
	GENERATED_BODY()

public:
	UPlayMontageGameplayEventObject();

	void InitializeWithData(UAnimMontage* InMontageToPlay, TArray<FName> InSectionNames, float InMinTime, float InMaxTime, UBehaviorTreeComponent* InCompThatCalledThis, UBTTaskNode* InTaskNode);

	UFUNCTION(BlueprintCallable)
	void FinishLatentTaskUsingTaskNode() const;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* MontageToPlay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> SectionNames;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MinTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxTime;

	UPROPERTY()
	UBehaviorTreeComponent* CompThatCalledThis;

	UPROPERTY()
	UBTTaskNode* TaskNode;

};
