// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "CreatureExpressionComponent.generated.h"

class UDataTable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CREATUREOASIS_API UCreatureExpressionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCreatureExpressionComponent();

	UFUNCTION(BlueprintCallable)
	void SetEyeTag(const FGameplayTag NewEyeTag);
	
	UFUNCTION(BlueprintCallable)
	void SetMouthTag(const FGameplayTag NewMouthTag);

	void RegenerateEyes() const;
	void RegenerateMouth() const;

protected:
	virtual void InitializeComponent() override;

	UMaterialInstanceDynamic* GetMaterialInstance(const FName MaterialName) const;
	
	UPROPERTY(EditAnywhere)
	UDataTable* EyeDataTable;
	
	UPROPERTY(EditAnywhere)
	UDataTable* MouthDataTable;
	
private:
	void PrepareMaterialInstances();
	
	UPROPERTY()
	class ACreatureCharacter* CreatureCharacter;
	UPROPERTY()
	class USkeletalMeshComponent* CreatureMesh;

	UPROPERTY()
	class UMaterialInstanceDynamic* EyeMaterialInstance;
	
	UPROPERTY()
	class UMaterialInstanceDynamic* MouthMaterialInstance;
	UPROPERTY()
	class UMaterialInstanceDynamic* SubMouthMaterialInstance;

	// Used for defaulting back to, generated based on personality
	UPROPERTY()
	FGameplayTag InitialEyeTag;
	UPROPERTY()
	FGameplayTag InitialMouthTag;

	UPROPERTY()
	FGameplayTag CurrentEyeTag;
	UPROPERTY()
	FGameplayTag CurrentMouthTag;
};
