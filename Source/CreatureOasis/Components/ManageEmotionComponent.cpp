// Fill out your copyright notice in the Description page of Project Settings.


#include "ManageEmotionComponent.h"

#include "CreatureOasis/Creature/CreatureCharacter.h"

// Sets default values for this component's properties
UManageEmotionComponent::UManageEmotionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}


// Called when the game starts
void UManageEmotionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UManageEmotionComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	CreatureCharacter = Cast<ACreatureCharacter>(GetOwner());
	CreatureMesh = CreatureCharacter->GetMesh();

	SetMouthMaterialInstance();
}


// Called every frame
void UManageEmotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UManageEmotionComponent::SetMouthMaterialInstance()
{
	MiddleMouthMaterialInstance = Cast<UMaterialInstanceDynamic>(CreatureMesh->GetMaterial(CreatureMesh->GetMaterialIndex(TEXT("M_mouth_middle"))));
	SideMouthMaterialInstance   = Cast<UMaterialInstanceDynamic>(CreatureMesh->GetMaterial(CreatureMesh->GetMaterialIndex(TEXT("M_mouth_side"))));

}

