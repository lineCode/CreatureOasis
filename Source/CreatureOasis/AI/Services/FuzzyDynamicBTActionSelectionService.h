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
class CREATUREOASIS_API UFuzzyDynamicBTActionSelectionService : public UBTService_BlueprintBase
{
	GENERATED_BODY()

public:
	UFuzzyDynamicBTActionSelectionService();
	
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;

protected:
	void SearchForBestFuzzyAction();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UBaseDynamicBTAction*> FuzzyActions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag DynamicBTInjectionTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBehaviorTree* BestFuzzyAction2;

	
private: 
	UPROPERTY()
	UBaseDynamicBTAction* BestFuzzyAction;
};
