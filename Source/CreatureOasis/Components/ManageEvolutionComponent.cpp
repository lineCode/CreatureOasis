// Fill out your copyright notice in the Description page of Project Settings.


#include "ManageEvolutionComponent.h"

#include "CreatureOasis/Creature/CreatureCharacter.h"

// Sets default values for this component's properties
UManageEvolutionComponent::UManageEvolutionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}

void UManageEvolutionComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	CreatureCharacter = Cast<ACreatureCharacter>(GetOwner());
	SetSkeletalMesh(CreatureCharacter->GetMesh());
}

// Called when the game starts
void UManageEvolutionComponent::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void UManageEvolutionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UManageEvolutionComponent::SetPrimaryColor(const FLinearColor NewColor) const
{
	if (IsValid(CreatureMesh))
	{
		CreatureMesh->SetVectorParameterValueOnMaterials(TEXT("PrimaryColor"), FVector(NewColor));
	}
	
}

void UManageEvolutionComponent::SetSecondaryColor(const FLinearColor NewColor) const
{
	if (IsValid(CreatureMesh))
	{
		CreatureMesh->SetVectorParameterValueOnMaterials(TEXT("SecondaryColor"), FVector(NewColor));
	}
}

void UManageEvolutionComponent::SetSkeletalMesh(USkeletalMeshComponent* NewMesh)
{
	CreatureMesh = NewMesh;
}

