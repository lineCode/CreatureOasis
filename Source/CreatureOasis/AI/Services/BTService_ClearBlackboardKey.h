// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"

#include "BTService_ClearBlackboardKey.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API UBTService_ClearBlackboardKey : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_ClearBlackboardKey();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere)
	bool bClearOnBecomeRelevant;

	UPROPERTY(EditAnywhere)
	bool bClearOnCeaseRelevant;
};
