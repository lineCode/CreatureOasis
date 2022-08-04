#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckGameplayTagsOnActorWithAbort.generated.h"

class UAbilityAsync_WaitGameplayTagAdded;
class UAbilitySystemComponent;

/**
 * Mostly similar to the build in CheckGameplayTagsOnActor but this one allows Aborting and uses the GAS system directly
 */
UCLASS()
class CREATUREOASIS_API UBTDecorator_CheckGameplayTagsOnActorWithAbort : public UBTDecorator
{
	GENERATED_BODY()

	UBTDecorator_CheckGameplayTagsOnActorWithAbort();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
	
	UAbilitySystemComponent* GetASCFromActor(const AActor* TargetActor) const; 
	
protected:
	UPROPERTY(EditAnywhere, Category=GameplayTagCheck,
		Meta=(ToolTips="Which Actor (from the blackboard) should be checked for these gameplay tags?"))
	FBlackboardKeySelector ActorToCheck;

	UPROPERTY(EditAnywhere, Category=GameplayTagCheck)
	FGameplayTag GameplayTag;

	TMap<FGameplayTag, FDelegateHandle> DelegateMap;
};
