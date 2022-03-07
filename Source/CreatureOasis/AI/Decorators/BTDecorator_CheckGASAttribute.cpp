// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_CheckGASAttribute.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "CreatureOasis/GameplayAbilitySystem/GASCharacter.h"

UBTDecorator_CheckGASAttribute::UBTDecorator_CheckGASAttribute()
{
	NodeName = TEXT("CheckGASAttribute");

	bNotifyActivation	= false;
	bNotifyDeactivation = false;
	bNotifyProcessed	= false;
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

bool UBTDecorator_CheckGASAttribute::CommenceComparativeCheck(const float ValToCheck) const
{
	bool CompareCheck = false;
	
	switch (CheckQuery)
	{
	case ECheckCompareQuery::Less:
		CompareCheck = ComparativeVal < ValToCheck;
		break;

	case ECheckCompareQuery::LessOrEqual:
		CompareCheck = ComparativeVal <= ValToCheck;
		break;

	case ECheckCompareQuery::Equal:
		CompareCheck = ComparativeVal == ValToCheck;
		break;

	case ECheckCompareQuery::Greater:
		CompareCheck = ComparativeVal > ValToCheck ;
		break;

	case ECheckCompareQuery::GreaterOrEqual:
		CompareCheck = ComparativeVal >= ValToCheck;
		break;
		
	default: ;
	}
	
	return CompareCheck;
}
