// Fill out your copyright notice in the Description page of Project Settings.


#include "ExpressionComponent.h"

#include "CreatureOasis/Characters/Creature/CreatureCharacter.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayTag.h"

#include "CreatureOasis/Structs/EyeTextureTagTableRow.h"
#include "CreatureOasis/Structs/MouthTextureTagTableRow.h"

#include "Engine/DataTable.h"

// Sets default values for this component's properties
UExpressionComponent::UExpressionComponent()
{
	//PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

}

void UExpressionComponent::SetEyeTag(const FGameplayTag NewEyeTag)
{
	CurrentEyeTag = NewEyeTag;
	RegenerateEyes();
}

void UExpressionComponent::SetMouthTag(const FGameplayTag NewMouthTag)
{
	CurrentMouthTag = NewMouthTag;
	RegenerateMouth();
}

void UExpressionComponent::RegenerateEyes() const
{
	if (!IsValid(EyeDataTable) || !CurrentEyeTag.IsValid())
	{
		return;
	}
	
	FEyeTextureTagTableRow* EyeTableRow = EyeDataTable->FindRow<FEyeTextureTagTableRow>(CurrentEyeTag.GetTagName(), "");

	if (EyeTableRow == nullptr, EyeTableRow->EyeTexture == nullptr)
	{
		return;
	}
	
	EyeMaterialInstance->SetTextureParameterValue("EyeTexture", EyeTableRow->EyeTexture);
}

void UExpressionComponent::RegenerateMouth() const
{
	if (!IsValid(MouthDataTable) || !CurrentMouthTag.IsValid())
	{
		return;
	}

	const FMouthTextureTagTableRow* const MouthTableRow = MouthDataTable->FindRow<FMouthTextureTagTableRow>(CurrentMouthTag.GetTagName(), "");
	
	if (MouthTableRow == nullptr || MouthTableRow->MouthTexture == nullptr)
	{
		return;
	}
	
	MouthMaterialInstance->SetTextureParameterValue("MainMouthTexture", MouthTableRow->MouthTexture);

	if (MouthTableRow->SideMouthTexture == nullptr)
	{
		return;
	}

	SubMouthMaterialInstance->SetTextureParameterValue("SideMouthTexture", MouthTableRow->SideMouthTexture);
}

UMaterialInstanceDynamic* UExpressionComponent::GetMaterialInstance(const FName MaterialName) const
{
	return Cast<UMaterialInstanceDynamic>(CreatureMesh->GetMaterial(CreatureMesh->GetMaterialIndex(MaterialName)));
}

void UExpressionComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	CreatureCharacter = Cast<ACreatureCharacter>(GetOwner());
	CreatureMesh = CreatureCharacter->GetMesh();

	PrepareMaterialInstances();
}

void UExpressionComponent::PrepareMaterialInstances()
{
	EyeMaterialInstance = GetMaterialInstance("M_eyes");
	
	MouthMaterialInstance = GetMaterialInstance("M_mouth_middle");
	SubMouthMaterialInstance = GetMaterialInstance("M_mouth_side");
}

