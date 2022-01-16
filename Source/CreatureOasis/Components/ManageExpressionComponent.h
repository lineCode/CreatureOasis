// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "ManageExpressionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CREATUREOASIS_API UManageExpressionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UManageExpressionComponent();

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
	class UDataTable* EyeDataTable;
	
	UPROPERTY(EditAnywhere)
	class UDataTable* MouthDataTable;
	
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

	UPROPERTY()
	FGameplayTag DefaultEyeTag;
	UPROPERTY()
	FGameplayTag DefaultMouthTag;

	UPROPERTY()
	FGameplayTag CurrentEyeTag;
	UPROPERTY()
	FGameplayTag CurrentMouthTag;
};
