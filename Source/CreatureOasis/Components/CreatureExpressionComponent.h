// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "CreatureOasis/Interfaces/CreatureComponentLoadableInterface.h"
#include "CreatureExpressionComponent.generated.h"

class UDataTable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CREATUREOASIS_API UCreatureExpressionComponent : public UActorComponent, public ICreatureComponentLoadableInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCreatureExpressionComponent();

	UFUNCTION()
	void GenerateInitialExpressionTags();
	
	UFUNCTION(BlueprintCallable)
	void SetEyeTag(const FGameplayTag NewEyeTag);
	
	UFUNCTION(BlueprintCallable)
	void SetMouthTag(const FGameplayTag NewMouthTag);

	UFUNCTION(BlueprintCallable)
	void ClearEyeTag();

	UFUNCTION(BlueprintCallable)
	void ClearMouthTag();
	
	UFUNCTION(BlueprintCallable)
	void ClearEyeAndMouthTag();
	
	UFUNCTION(BlueprintCallable)
	FGameplayTag GetActiveEyeTag() const;
	
	UFUNCTION(BlueprintCallable)
	FGameplayTag GetActiveMouthTag() const;
	
protected:
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	
	void RegenerateEyesAndMouth() const;
	void RegenerateEyes() const;
	void RegenerateMouth() const;
	
	virtual void LoadCreatureData_Implementation(const FCreatureDataLoad& CreatureDataLoad) override;
	virtual void GatherCreatureData_Implementation(FCreatureDataLoad& CreatureDataLoad) override;
	
	UMaterialInstanceDynamic* CreateAndSetMaterialInstanceDynamic(const FName MaterialName) const;
	void PrepareMaterialInstances();

	UPROPERTY(EditAnywhere)
	UDataTable* EyeDataTable;
	
	UPROPERTY(EditAnywhere)
	UDataTable* MouthDataTable;
	
private:
	UPROPERTY()
	class ACreatureCharacter* CreatureCharacter;
	
	UPROPERTY()
	USkeletalMeshComponent* CreatureMesh;

	UPROPERTY()
	UMaterialInstanceDynamic* EyeMaterialInstance;
	
	UPROPERTY()
	UMaterialInstanceDynamic* MouthMaterialInstance;
	UPROPERTY()
	UMaterialInstanceDynamic* SubMouthMaterialInstance;

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
