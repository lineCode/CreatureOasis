// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"

#include "FuzzyDynamicBTActionSelectionService.generated.h"

class IFuzzyLogicInterface;
class UBaseDynamicBTAction;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class CREATUREOASIS_API UFuzzyDynamicBTActionSelectionService : public UBTService
{
	GENERATED_BODY()

public:
	UFuzzyDynamicBTActionSelectionService();
	
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
protected:
	void SearchForBestFuzzyAction(const UBehaviorTreeComponent& OwnerComp);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<UBaseDynamicBTAction>> FuzzyActions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag DynamicBTInjectionTag;
	
private: 
	UPROPERTY()
	UBaseDynamicBTAction* BestFuzzyAction;
};
