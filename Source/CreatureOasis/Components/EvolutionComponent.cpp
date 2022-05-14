// Fill out your copyright notice in the Description page of Project Settings.


#include "EvolutionComponent.h"

#include "CreatureOasis/Characters/Creature/CreatureCharacter.h"

// Sets default values for this component's properties
UEvolutionComponent::UEvolutionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}

void UEvolutionComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	CreatureCharacter = Cast<ACreatureCharacter>(GetOwner());
	SetSkeletalMesh(CreatureCharacter->GetMesh());
}

// Called when the game starts
void UEvolutionComponent::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void UEvolutionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEvolutionComponent::SetPrimaryColor(const FLinearColor NewColor) const
{
	if (IsValid(CreatureMesh))
	{
		CreatureMesh->SetVectorParameterValueOnMaterials(TEXT("PrimaryColor"), FVector(NewColor));
	}
	
}

void UEvolutionComponent::SetSecondaryColor(const FLinearColor NewColor) const
{
	if (IsValid(CreatureMesh))
	{
		CreatureMesh->SetVectorParameterValueOnMaterials(TEXT("SecondaryColor"), FVector(NewColor));
	}
}

void UEvolutionComponent::SetSkeletalMesh(USkeletalMeshComponent* NewMesh)
{
	CreatureMesh = NewMesh;
}

