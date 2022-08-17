// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_CheckGASAttribute.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "CreatureOasis/GameplayAbilitySystem/GASCharacter.h"

UBTDecorator_CheckGASAttribute::UBTDecorator_CheckGASAttribute()
{
	NodeName = TEXT("CheckGASAttribute");

	bNotifyBecomeRelevant	= true;
	bNotifyCeaseRelevant	= true;
	bNotifyDeactivation		= false;
	bNotifyProcessed		= false;
}

void UBTDecorator_CheckGASAttribute::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	
	UAbilitySystemComponent* AbilitySystemComponent = GetASCFromActor(OwnerComp.GetAIOwner()->GetPawn());
	if (!IsValid(AbilitySystemComponent))
	{
		return;
	}

	FBTCheckGASAttributeMemory* Memory = CastInstanceNodeMemory<FBTCheckGASAttributeMemory>(NodeMemory);
	Memory->DelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TargetAttribute).AddLambda([&](const FOnAttributeChangeData& OnAttributeChangeData)
	{
		if (CommenceComparativeCheck(OnAttributeChangeData.NewValue))
		{
			OwnerComp.RequestExecution(this);
		}
	});
}

void UBTDecorator_CheckGASAttribute::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);

	// const UAbilitySystemComponent* AbilitySystemComponent = GetASCFromActor(OwnerComp.GetAIOwner()->GetPawn());
	// if (!IsValid(AbilitySystemComponent))
	// {
	// 	return;
	// }
	
	FBTCheckGASAttributeMemory* Memory = CastInstanceNodeMemory<FBTCheckGASAttributeMemory>(NodeMemory);
	Memory->DelegateHandle.Reset();
}

bool UBTDecorator_CheckGASAttribute::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (TargetAttribute.IsValid() && IsValid(OwnerComp.GetAIOwner()))
	{
		const AGASCharacter* GASCharacter = Cast<AGASCharacter>(OwnerComp.GetAIOwner()->GetPawn());
		if(IsValid(GASCharacter))
		{
			const UAbilitySystemComponent* AbilitySystemComponent = GASCharacter->GetAbilitySystemComponent();
			return CommenceComparativeCheck(AbilitySystemComponent->GetNumericAttributeBase(TargetAttribute));
		}
	}

	return false;
}

uint16 UBTDecorator_CheckGASAttribute::GetInstanceMemorySize() const
{
	return sizeof(FBTCheckGASAttributeMemory);
}

bool UBTDecorator_CheckGASAttribute::CommenceComparativeCheck(const float ValToCheck) const
{
	bool CompareCheck = false;
	
	switch (CheckQuery)
	{
	case ECheckCompareQuery::Less:
		CompareCheck = ScalableFloat.GetValue() < ValToCheck;
		break;

	case ECheckCompareQuery::LessOrEqual:
		CompareCheck = ScalableFloat.GetValue() <= ValToCheck;
		break;

	case ECheckCompareQuery::Equal:
		CompareCheck = ScalableFloat.GetValue() == ValToCheck;
		break;

	case ECheckCompareQuery::Greater:
		CompareCheck = ScalableFloat.GetValue() > ValToCheck ;
		break;

	case ECheckCompareQuery::GreaterOrEqual:
		CompareCheck = ScalableFloat.GetValue() >= ValToCheck;
		break;
		
	default: ;
	}
	
	return CompareCheck;
}

UAbilitySystemComponent* UBTDecorator_CheckGASAttribute::GetASCFromActor(const AActor* TargetActor) const
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
