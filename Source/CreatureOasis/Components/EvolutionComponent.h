// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EvolutionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CREATUREOASIS_API UEvolutionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEvolutionComponent();

protected:
	virtual void InitializeComponent() override;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetPrimaryColor(const FLinearColor NewColor) const;
	
	UFUNCTION(BlueprintCallable)
	void SetSecondaryColor(const FLinearColor NewColor) const;

	UFUNCTION(BlueprintCallable)
	void SetSkeletalMesh(USkeletalMeshComponent* NewMesh);
	
private:
	UPROPERTY()
	class ACreatureCharacter* CreatureCharacter;

	UPROPERTY()
	class USkeletalMeshComponent* CreatureMesh;
};
