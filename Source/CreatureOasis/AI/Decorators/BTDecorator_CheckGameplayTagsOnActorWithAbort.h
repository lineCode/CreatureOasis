#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckGameplayTagsOnActorWithAbort.generated.h"

/**
 * Mostly similar to the build in CheckGameplayTagsOnActor but this one allows Aborting and uses the GAS system directly
 */
UCLASS()
class CREATUREOASIS_API UBTDecorator_CheckGameplayTagsOnActorWithAbort : public UBTDecorator
{
	GENERATED_BODY()

	UBTDecorator_CheckGameplayTagsOnActorWithAbort();
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;

protected:

	UPROPERTY(EditAnywhere, Category=GameplayTagCheck,
		Meta=(ToolTips="Which Actor (from the blackboard) should be checked for these gameplay tags?"))
	struct FBlackboardKeySelector ActorToCheck;

	UPROPERTY(EditAnywhere, Category=GameplayTagCheck)
	EGameplayContainerMatchType TagsToMatch;

	UPROPERTY(EditAnywhere, Category=GameplayTagCheck)
	FGameplayTagContainer GameplayTags;
};
