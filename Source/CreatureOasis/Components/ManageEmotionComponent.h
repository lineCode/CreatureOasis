// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ManageEmotionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CREATUREOASIS_API UManageEmotionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UManageEmotionComponent();

protected:
	virtual void InitializeComponent() override;

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	void SetMouthMaterialInstance();
	
	UPROPERTY()
	class ACreatureCharacter* CreatureCharacter;
	UPROPERTY()
	class USkeletalMeshComponent* CreatureMesh;

	UPROPERTY()
	class UMaterialInstanceDynamic* MiddleMouthMaterialInstance;
	UPROPERTY()
	class UMaterialInstanceDynamic* SideMouthMaterialInstance;
};
