// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureAppearanceComponent.h"

#include "AbilitySystemComponent.h"
#include "CreatureOasis/Characters/Creature/CreatureCharacter.h"
#include "CreatureOasis/Structs/ProjectSettings/GardenSettings.h"

// Sets default values for this component's properties
UCreatureAppearanceComponent::UCreatureAppearanceComponent()
	: EvolutionStateTag(FGameplayTag::RequestGameplayTag("State.Chao.Evolution.Egg"))
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
}

// Called when the game starts
void UCreatureAppearanceComponent::BeginPlay()
{
	Super::BeginPlay();
	
	RegenerateMesh();
}

void UCreatureAppearanceComponent::SetEvolutionStateTag(const FGameplayTag InEvolutionStateTag, const bool bRegenerateMesh)
{
	if (!InEvolutionStateTag.IsValid())
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

void UCreatureAppearanceComponent::RegenerateMesh() const
{
	const UGardenSettings* GardenSettings = GetDefault<UGardenSettings>();
	
	if (EvolutionStateTag.IsValid() && GardenSettings->EvolutionStateTagSkeletalMeshMap.Contains(EvolutionStateTag))
	{
		const FEvolutionStateData* EvolutionStateData = GardenSettings->EvolutionStateTagSkeletalMeshMap.Find(EvolutionStateTag);
		
		if (EvolutionStateTag == EggStateTag)
		{
			//CreatureMesh->SetAnimInstanceClass(DefaultEggAnimClass);
			CreatureMesh->SetSkeletalMesh(EvolutionStateData->SkeletalMesh, false);

		}
		else
		{
			CreatureMesh->SetSkeletalMesh(EvolutionStateData->SkeletalMesh, false);

			CreatureMesh->SetAnimInstanceClass(DefaultChaoAnimClass);
			//CreatureMesh->Play();
			//
			// CreatureMesh->ClearAnimScriptInstance();
			// CreatureMesh->AnimClass = DefaultChaoAnimClass;
			// CreatureMesh->ClearAnimScriptInstance();
			// CreatureMesh->InitAnim(true);
			// CreatureMesh->InitializeAnimScriptInstance();

		}
	}
}

void UCreatureAppearanceComponent::LoadCreatureData_Implementation(const FCreatureDataLoad& CreatureDataLoad)
{
	InitialPrimaryColor = CreatureDataLoad.InitialPrimaryColor;
	InitialSecondaryColor = CreatureDataLoad.InitialSecondaryColor;
	
	SetEvolutionStateTag(CreatureDataLoad.EvolutionStateTag);
}

void UCreatureAppearanceComponent::GatherCreatureData_Implementation(FCreatureDataLoad& CreatureDataLoad)
{
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

