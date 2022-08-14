// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "UObject/Object.h"
#include "BTService_SetBoolBlackboardKey.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UBTService_SetBoolBlackboardKey : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_SetBoolBlackboardKey();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere)
	bool bSetOnBecomeRelevant;

	UPROPERTY(EditAnywhere)
	bool bSetOnCeaseRelevant;
};
