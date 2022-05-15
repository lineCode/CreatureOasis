#include "CreatureExpressionComponent.h"

#include "CreatureOasis/Characters/Creature/CreatureCharacter.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayTag.h"

#include "CreatureOasis/Structs/EyeTextureTagTableRow.h"
#include "CreatureOasis/Structs/MouthTextureTagTableRow.h"

#include "Engine/DataTable.h"

UCreatureExpressionComponent::UCreatureExpressionComponent()
{
	//PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

}

void UCreatureExpressionComponent::SetEyeTag(const FGameplayTag NewEyeTag)
{
	CurrentEyeTag = NewEyeTag;
	RegenerateEyes();
}

void UCreatureExpressionComponent::SetMouthTag(const FGameplayTag NewMouthTag)
{
	CurrentMouthTag = NewMouthTag;
	RegenerateMouth();
}

void UCreatureExpressionComponent::RegenerateEyes() const
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

void UCreatureExpressionComponent::RegenerateMouth() const
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

UMaterialInstanceDynamic* UCreatureExpressionComponent::GetMaterialInstance(const FName MaterialName) const
{
	return Cast<UMaterialInstanceDynamic>(CreatureMesh->GetMaterial(CreatureMesh->GetMaterialIndex(MaterialName)));
}

void UCreatureExpressionComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	CreatureCharacter = Cast<ACreatureCharacter>(GetOwner());
	CreatureMesh = CreatureCharacter->GetMesh();

	PrepareMaterialInstances();
}

void UCreatureExpressionComponent::PrepareMaterialInstances()
{
	EyeMaterialInstance = GetMaterialInstance("M_eyes");
	
	MouthMaterialInstance = GetMaterialInstance("M_mouth_middle");
	SubMouthMaterialInstance = GetMaterialInstance("M_mouth_side");
}

