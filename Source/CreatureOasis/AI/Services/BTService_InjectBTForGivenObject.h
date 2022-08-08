// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_InjectBTForGivenObject.generated.h"

USTRUCT(BlueprintType)
struct FTreeTagElement
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer TagContainer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBehaviorTree* BehaviorTree;
};

/**
 * BTService used for determining what BT to run depending on what tag type of actor is being held at the moment
 */
UCLASS()
class CREATUREOASIS_API UBTService_InjectBTForGivenObject : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_InjectBTForGivenObject();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FTreeTagElement> PossibleTreeArray;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag DynamicBTInjectionTag;
};
