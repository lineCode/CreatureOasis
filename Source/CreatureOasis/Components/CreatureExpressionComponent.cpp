#include "CreatureExpressionComponent.h"

#include "CreatureOasis/Characters/Creature/CreatureCharacter.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayTag.h"
#include "CreatureOasis/BlueprintLibraries/CreatureOasisBlueprintLibrary.h"

#include "CreatureOasis/Structs/EyeTextureTagTableRow.h"
#include "CreatureOasis/Structs/MouthTextureTagTableRow.h"

#include "Engine/DataTable.h"

UCreatureExpressionComponent::UCreatureExpressionComponent()
	: InitialEyeTag(FGameplayTag::EmptyTag)
	, InitialMouthTag(FGameplayTag::EmptyTag)
{
	bWantsInitializeComponent = true;
}

void UCreatureExpressionComponent::GenerateInitialExpressionTags()
{
	if (!InitialEyeTag.IsValid())
	{
		InitialEyeTag = FGameplayTag::RequestGameplayTag(TEXT("FaceExpression.Creature.Eyes.Normal"));
	}

	if (!InitialMouthTag.IsValid())
	{
		InitialMouthTag = FGameplayTag::RequestGameplayTag(TEXT("FaceExpression.Creature.Mouth.Invisible"));
	}

	RegenerateEyesAndMouth();
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

void UCreatureExpressionComponent::SetRandomEyeTag(const FGameplayTagContainer NewEyeTagContainer)
{
	FGameplayTag Tag;
	UCreatureOasisBlueprintLibrary::GetRandomTagFromGameplayTagContainer(NewEyeTagContainer, Tag);
	SetEyeTag(Tag);
}

void UCreatureExpressionComponent::SetRandomMouthTag(const FGameplayTagContainer NewMouthTagContainer)
{
	FGameplayTag Tag;
	UCreatureOasisBlueprintLibrary::GetRandomTagFromGameplayTagContainer(NewMouthTagContainer, Tag);
	SetMouthTag(Tag);
}

void UCreatureExpressionComponent::ClearEyeTag()
{
	SetEyeTag(FGameplayTag::EmptyTag);
}

void UCreatureExpressionComponent::ClearMouthTag()
{
	SetMouthTag(FGameplayTag::EmptyTag);
}

void UCreatureExpressionComponent::ClearEyeAndMouthTag()
{
	CurrentEyeTag = FGameplayTag::EmptyTag;
	CurrentMouthTag = FGameplayTag::EmptyTag;
	RegenerateEyesAndMouth();
}

FGameplayTag UCreatureExpressionComponent::GetActiveEyeTag() const
{
	return CurrentEyeTag.IsValid() ? CurrentEyeTag : InitialEyeTag;
}

FGameplayTag UCreatureExpressionComponent::GetActiveMouthTag() const
{
	return CurrentMouthTag.IsValid() ? CurrentMouthTag : InitialMouthTag;
}

void UCreatureExpressionComponent::RegenerateEyes() const
{
	if (EyeMaterialInstance == nullptr || !IsValid(EyeDataTable))
	{
		return;
	}
	
	FName RowName;
	if (UCreatureOasisBlueprintLibrary::GetNameOfTopMostChildTag(GetActiveEyeTag(), RowName))
	{
		const FEyeTextureTagTableRow* EyeTableRow = EyeDataTable->FindRow<FEyeTextureTagTableRow>(RowName, "");
		if (EyeTableRow == nullptr)
		{
			return;
		}
	
		EyeMaterialInstance->SetTextureParameterValue("EyeTexture", EyeTableRow->EyeTexture);
	}
}

void UCreatureExpressionComponent::RegenerateMouth() const
{
	if (MouthMaterialInstance == nullptr || SubMouthMaterialInstance == nullptr || !IsValid(MouthDataTable))
	{
		return;
	}
	
	FName RowName;
	if (UCreatureOasisBlueprintLibrary::GetNameOfTopMostChildTag(GetActiveMouthTag(), RowName))
	{
		const FMouthTextureTagTableRow* const MouthTableRow = MouthDataTable->FindRow<FMouthTextureTagTableRow>(RowName, "");
		if (MouthTableRow == nullptr)
		{
			return;
		}

		MouthMaterialInstance->SetTextureParameterValue("MainMouthTexture", IsValid(MouthTableRow->MouthTexture) ? MouthTableRow->MouthTexture : FallbackTexture);

		SubMouthMaterialInstance->SetTextureParameterValue("SideMouthTexture", IsValid(MouthTableRow->SideMouthTexture) ? MouthTableRow->SideMouthTexture : FallbackTexture);
	}
}

void UCreatureExpressionComponent::LoadCreatureData_Implementation(const FCreatureDataLoad& CreatureDataLoad)
{
	InitialEyeTag = CreatureDataLoad.InitialEyeTag;
	InitialMouthTag = CreatureDataLoad.InitialMouthTag;

	RegenerateEyesAndMouth();
}

void UCreatureExpressionComponent::GatherCreatureData_Implementation(FCreatureDataLoad& CreatureDataLoad)
{
	CreatureDataLoad.InitialEyeTag = InitialEyeTag;
	CreatureDataLoad.InitialMouthTag = InitialMouthTag;
}

void UCreatureExpressionComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	CreatureCharacter = Cast<ACreatureCharacter>(GetOwner());
	CreatureMesh = CreatureCharacter->GetMesh();
	PrepareMaterialInstances();
}

void UCreatureExpressionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	GenerateInitialExpressionTags();
}

void UCreatureExpressionComponent::RegenerateEyesAndMouth() const
{
	RegenerateEyes();
	RegenerateMouth();
}

UMaterialInstanceDynamic* UCreatureExpressionComponent::CreateAndSetMaterialInstanceDynamic(const FName MaterialName) const
{
	const int32 MatIndex = CreatureMesh->GetMaterialIndex(MaterialName);
	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(CreatureMesh->GetMaterial(MatIndex), CreatureMesh);
	CreatureMesh->SetMaterial(MatIndex, DynamicMaterial);
	return DynamicMaterial;
}

void UCreatureExpressionComponent::PrepareMaterialInstances()
{
	EyeMaterialInstance = CreateAndSetMaterialInstanceDynamic("M_eyes");
	
	MouthMaterialInstance = CreateAndSetMaterialInstanceDynamic("M_mouth_middle");
	SubMouthMaterialInstance = CreateAndSetMaterialInstanceDynamic("M_mouth_sides");
}

