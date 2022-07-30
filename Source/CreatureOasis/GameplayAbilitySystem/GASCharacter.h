// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"

#include "GASCharacter.generated.h"

UCLASS()
class CREATUREOASIS_API AGASCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;
	
public:
	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	// Called to bind functionality to input
	virtual void PossessedBy(AController* NewController) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	virtual void InitializeAttributes();
	virtual void AddStartupEffects();
	virtual void GiveAbilities();
	virtual void RemoveCharacterAbilities();

	float GetCharacterLevel() const;

	// list of default gameplay abilities
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	TArray<TSubclassOf<class UBaseGameplayAbility>> CharacterAbilities;
	
	// Effect that initializes our default attributes
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	// Adds loose gameplay tags at start which are not backed by a GameplayEffect
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS")
	FGameplayTagContainer StartupGameplayTags;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="GAS")
	class UBaseAbilitySystemComponent* AbilitySystemComponent;

protected:
	UPROPERTY()
	const class UBaseAttributeSet* BaseAttributeSet;
};
