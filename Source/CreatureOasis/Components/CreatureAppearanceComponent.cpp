// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureAppearanceComponent.h"

#include "CreatureOasis/Characters/Creature/CreatureCharacter.h"

// Sets default values for this component's properties
UCreatureAppearanceComponent::UCreatureAppearanceComponent()
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

}

void UCreatureAppearanceComponent::LoadCreatureData_Implementation(const FCreatureDataLoad& CreatureDataLoad)
{
	InitialPrimaryColor = CreatureDataLoad.InitialPrimaryColor;
	InitialSecondaryColor = CreatureDataLoad.InitialSecondaryColor;
}

void UCreatureAppearanceComponent::GatherCreatureData_Implementation(FCreatureDataLoad& CreatureDataLoad)
{
	CreatureDataLoad.InitialPrimaryColor = InitialPrimaryColor;
	CreatureDataLoad.InitialSecondaryColor = InitialSecondaryColor;
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

