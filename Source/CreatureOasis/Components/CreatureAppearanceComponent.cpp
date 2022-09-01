// Fill out your copyright notice in the Description page of Project Settings.

#include "CreatureAppearanceComponent.h"

#include "AbilitySystemComponent.h"
#include "CreatureOasis/Characters/Creature/CreatureCharacter.h"
#include "CreatureOasis/Structs/ProjectSettings/GardenSettings.h"

// Sets default values for this component's properties
UCreatureAppearanceComponent::UCreatureAppearanceComponent()
	: ColorTag(FGameplayTag::RequestGameplayTag("Color.Normal"))
	, EvolutionStateTag(FGameplayTag::RequestGameplayTag("State.Chao.Evolution.Egg"))
	, EggStateTag(FGameplayTag::RequestGameplayTag("State.Chao.Evolution.Egg"))
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}

void UCreatureAppearanceComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	CreatureCharacter = Cast<ACreatureCharacter>(GetOwner());
	SetSkeletalMesh(CreatureCharacter->GetMesh());

	PrepareMaterialInstances();
}

void UCreatureAppearanceComponent::UninitializeComponent()
{
	Super::UninitializeComponent();

	ClearAttributeListeners();
}

// Called when the game starts
void UCreatureAppearanceComponent::BeginPlay()
{
	Super::BeginPlay();
	
	RegenerateMesh();
	SetColorTag(FGameplayTag::RequestGameplayTag("Color.Normal"));
}

void UCreatureAppearanceComponent::SetEvolutionStateTag(const FGameplayTag InEvolutionStateTag, const bool bRegenerateMesh)
{
	if (!InEvolutionStateTag.IsValid() || EvolutionStateTag == InEvolutionStateTag)
	{
		return;
	}
	
	EvolutionStateTag = InEvolutionStateTag;

	FGameplayEventData EventData;
	EventData.TargetTags = FGameplayTagContainer(InEvolutionStateTag);
	CreatureCharacter->GetAbilitySystemComponent()->HandleGameplayEvent(FGameplayTag::RequestGameplayTag("Event.Chao.EvolutionStateChanged"), &EventData);

	if (bRegenerateMesh)
	{
		RegenerateMesh();
	}
}

FGameplayTag UCreatureAppearanceComponent::GetEvolutionStateTag() const
{
	return EvolutionStateTag;
}

void UCreatureAppearanceComponent::RegenerateMesh()
{
	const UGardenSettings* GardenSettings = GetDefault<UGardenSettings>();
	
	if (EvolutionStateTag.IsValid() && GardenSettings->EvolutionStateTagSkeletalMeshMap.Contains(EvolutionStateTag))
	{
		const FEvolutionStateData* EvolutionStateData = GardenSettings->EvolutionStateTagSkeletalMeshMap.Find(EvolutionStateTag);
		
		if (EvolutionStateTag == EggStateTag)
		{
			CreatureMesh->SetSkeletalMesh(EvolutionStateData->SkeletalMesh, false);
		}
		else
		{
			CreatureMesh->SetSkeletalMesh(EvolutionStateData->SkeletalMesh, false);

			CreatureMesh->SetAnimInstanceClass(DefaultChaoAnimClass);
		}

		ClearAttributeListeners();

		const FGradualEvolutionData* GradualEvolutionData = GardenSettings->GradualEvolutionAttributeMap.Find(EvolutionStateTag);

		if (GradualEvolutionData != nullptr && !GradualEvolutionData->GradualEvolutionDataEntries.IsEmpty())
		{
			TArray<FGameplayAttribute> GameplayAttributes;
			GradualEvolutionData->GradualEvolutionDataEntries.GetKeys(GameplayAttributes);
			
			for (const FGameplayAttribute Attribute : GameplayAttributes)
			{
				const FGradualEvolutionDataEntry* DataEntry = GradualEvolutionData->GradualEvolutionDataEntries.Find(Attribute);

				FOnGameplayAttributeValueChange& AttributeChange = CreatureCharacter->GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(Attribute);
				AttributeListenerHandles.Add(AttributeChange.AddLambda([&, DataEntry](FOnAttributeChangeData ChangeData)
				{
					const float NewValueModified = ((ChangeData.NewValue * 0.01f) * 2) - 1.f;
					
					if (NewValueModified < 0.f)
					{
						AlterMaterialUsingData(DataEntry->Left, FMath::Abs(NewValueModified));
					}
					else
					{
						AlterMaterialUsingData(DataEntry->Right, NewValueModified);
					}
				}));
			}
		}
	}
}

void UCreatureAppearanceComponent::ClearAttributeListeners()
{
	CreatureMesh->ClearMorphTargets();
	
	for (FDelegateHandle Handle : AttributeListenerHandles)
	{
		if (Handle.IsValid())
		{
			Handle.Reset();
		}
	}
	AttributeListenerHandles.Empty();
}

UMaterialInstanceDynamic* UCreatureAppearanceComponent::CreateAndSetMaterialInstanceDynamic(const FName MaterialName) const
{
	const int32 MatIndex = CreatureMesh->GetMaterialIndex(MaterialName);
	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(CreatureMesh->GetMaterial(MatIndex), CreatureMesh);
	CreatureMesh->SetMaterial(MatIndex, DynamicMaterial);
	return DynamicMaterial;
}

void UCreatureAppearanceComponent::PrepareMaterialInstances()
{
	BellyMaterialInstance = CreateAndSetMaterialInstanceDynamic("M_belly");
}

void UCreatureAppearanceComponent::AlterMaterialUsingData(const FGradualEvolutionDataSingleEntry& InDataEntry, const float Scale) const
{
	CreatureMesh->SetMorphTarget(InDataEntry.MorphTarget, Scale);

	if (InDataEntry.bOverrideColor)
	{
		SetPrimaryColor(FMath::Lerp(InitialPrimaryColor, InDataEntry.PrimaryColor, Scale));
		SetSecondaryColor(FMath::Lerp(InitialSecondaryColor, InDataEntry.SecondaryColor, Scale));
	}

	if (!InDataEntry.GradualEvolutionTextureArray.IsEmpty())
	{
		for (const FGradualEvolutionTextureData TextureData : InDataEntry.GradualEvolutionTextureArray)
		{
			BellyMaterialInstance->SetTextureParameterValue(TextureData.ParameterName, TextureData.Texture);
		}
	}
}

void UCreatureAppearanceComponent::LoadCreatureData_Implementation(const FCreatureDataLoad& CreatureDataLoad)
{
	InitialPrimaryColor = CreatureDataLoad.InitialPrimaryColor;
	InitialSecondaryColor = CreatureDataLoad.InitialSecondaryColor;

	SetColorTag(CreatureDataLoad.ColorTag);
	SetEvolutionStateTag(CreatureDataLoad.EvolutionStateTag);
}

void UCreatureAppearanceComponent::GatherCreatureData_Implementation(FCreatureDataLoad& CreatureDataLoad)
{
	CreatureDataLoad.ColorTag = ColorTag;
	CreatureDataLoad.InitialPrimaryColor = InitialPrimaryColor;
	CreatureDataLoad.InitialSecondaryColor = InitialSecondaryColor;
	
	CreatureDataLoad.EvolutionStateTag = EvolutionStateTag;
}

// Called every frame
void UCreatureAppearanceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCreatureAppearanceComponent::SetPrimaryColor(const FLinearColor NewColor) const
{
	if (IsValid(CreatureMesh))
	{
		CreatureMesh->SetVectorParameterValueOnMaterials(TEXT("PrimaryColor"), FVector(NewColor));
	}
}

void UCreatureAppearanceComponent::SetSecondaryColor(const FLinearColor NewColor) const
{
	if (IsValid(CreatureMesh))
	{
		CreatureMesh->SetVectorParameterValueOnMaterials(TEXT("SecondaryColor"), FVector(NewColor));
	}
}

void UCreatureAppearanceComponent::SetSkeletalMesh(USkeletalMeshComponent* NewMesh)
{
	CreatureMesh = NewMesh;
}

void UCreatureAppearanceComponent::SetColorTag(const FGameplayTag InColorTag, const FLinearColor InCustomPrimaryColor,
	const FLinearColor InCustomSecondaryColor)
{
	const UGardenSettings* GardenSettings = GetDefault<UGardenSettings>();

	if (GardenSettings->CreatureColorDataMap.Contains(InColorTag))
	{
		const FCreatureColorData* ColorData = GardenSettings->CreatureColorDataMap.Find(InColorTag);

		if (InColorTag == FGameplayTag::RequestGameplayTag("Color.Custom"))
        {
        	InitialPrimaryColor = InCustomPrimaryColor;
        	InitialSecondaryColor = InCustomSecondaryColor;
        }
        else
        {
        	InitialPrimaryColor = ColorData->PrimaryColor;
        	InitialSecondaryColor = ColorData->SecondaryColor;
        }
    
        ColorTag = InColorTag;
	}
}

