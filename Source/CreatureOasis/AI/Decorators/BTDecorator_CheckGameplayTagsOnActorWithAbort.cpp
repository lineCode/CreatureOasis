#include "BTDecorator_CheckGameplayTagsOnActorWithAbort.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "GameplayTagAssetInterface.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayTag.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "CreatureOasis/GameplayAbilitySystem/GASCharacter.h"

UBTDecorator_CheckGameplayTagsOnActorWithAbort::UBTDecorator_CheckGameplayTagsOnActorWithAbort()
{
	NodeName = "Gameplay Tag Condition";

	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
	
	// Accept only actors
	ActorToCheck.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_CheckGameplayTagsOnActorWithAbort, ActorToCheck), AActor::StaticClass());

	// Default to using Self Actor
	ActorToCheck.SelectedKeyName = FBlackboard::KeySelf;
}

void UBTDecorator_CheckGameplayTagsOnActorWithAbort::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	const AActor* TargetToCheck = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ActorToCheck.SelectedKeyName));

	UAbilitySystemComponent* AbilitySystemComponent = GetASCFromActor(TargetToCheck);
	if (!IsValid(AbilitySystemComponent))
	{
		return;
	}
	
	FDelegateHandle DelegateHandle = AbilitySystemComponent->RegisterGameplayTagEvent(GameplayTag, EGameplayTagEventType::NewOrRemoved).AddLambda([&](const FGameplayTag ResultTag, int32 Count)
	{
		UE_LOG(LogTemp, Warning, TEXT("Requesting Execution"));
		OwnerComp.RequestExecution(this);
	});

	DelegateMap.Add(TTuple<FGameplayTag, FDelegateHandle>(GameplayTag,DelegateHandle));
}

void UBTDecorator_CheckGameplayTagsOnActorWithAbort::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	const AActor* TargetToCheck = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ActorToCheck.SelectedKeyName));

	UAbilitySystemComponent* AbilitySystemComponent = GetASCFromActor(TargetToCheck);
	if (!IsValid(AbilitySystemComponent))
	{
		return;
	}

	AbilitySystemComponent->UnregisterGameplayTagEvent(DelegateMap.FindRef(GameplayTag), GameplayTag, EGameplayTagEventType::NewOrRemoved);
}

UAbilitySystemComponent* UBTDecorator_CheckGameplayTagsOnActorWithAbort::GetASCFromActor(const AActor* TargetActor) const
{
	const AGASCharacter* GASCharacter = Cast<AGASCharacter>(TargetActor);
	if(!IsValid(GASCharacter))
	{
		return nullptr;
	}

	UAbilitySystemComponent* AbilitySystemComponent = GASCharacter->GetAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent))
	{
		return nullptr;
	}

	return AbilitySystemComponent;
}

bool UBTDecorator_CheckGameplayTagsOnActorWithAbort::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                                                uint8* NodeMemory) const
{
	const AActor* TargetToCheck = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ActorToCheck.SelectedKeyName));

	const UAbilitySystemComponent* AbilitySystemComponent = GetASCFromActor(TargetToCheck);
	if (!IsValid(AbilitySystemComponent))
	{
		return false;
	}
	
	return AbilitySystemComponent->HasMatchingGameplayTag(GameplayTag);
}

void UBTDecorator_CheckGameplayTagsOnActorWithAbort::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);
}