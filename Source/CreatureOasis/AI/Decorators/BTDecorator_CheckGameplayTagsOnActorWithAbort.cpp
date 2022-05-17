#include "BTDecorator_CheckGameplayTagsOnActorWithAbort.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "GameplayTagAssetInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "CreatureOasis/GameplayAbilitySystem/GASCharacter.h"

UBTDecorator_CheckGameplayTagsOnActorWithAbort::UBTDecorator_CheckGameplayTagsOnActorWithAbort() :
	TagsToMatch()
{
	NodeName = "Gameplay Tag Condition With Abort";

	// Accept only actors
	ActorToCheck.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_CheckGameplayTagsOnActorWithAbort, ActorToCheck), AActor::StaticClass());

	// Default to using Self Actor
	ActorToCheck.SelectedKeyName = FBlackboard::KeySelf;
}

bool UBTDecorator_CheckGameplayTagsOnActorWithAbort::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                                                uint8* NodeMemory) const
{
	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp == nullptr)
	{
		return false;
	}
	
	const AGASCharacter* GASCharacter = Cast<AGASCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(!IsValid(GASCharacter))
	{
		return false;
	}

	const UAbilitySystemComponent* AbilitySystemComponent = GASCharacter->GetAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent))
	{
		return false;
	}
	
	switch (TagsToMatch)
	{
	case EGameplayContainerMatchType::All:
		return AbilitySystemComponent->HasAllMatchingGameplayTags(GameplayTags);

	case EGameplayContainerMatchType::Any:
		return AbilitySystemComponent->HasAnyMatchingGameplayTags(GameplayTags);

	default:
		{
			UE_LOG(LogBehaviorTree, Warning, TEXT("Invalid value for TagsToMatch (EGameplayContainerMatchType) %d.  Should only be Any or All."), static_cast<int32>(TagsToMatch));
			return false;
		}
	}
}

void UBTDecorator_CheckGameplayTagsOnActorWithAbort::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);
}