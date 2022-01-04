// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Pawn.h"
#include "GASPawn.generated.h"

/** 
 * GASPawn is the base class of all actors that should make use of the Gameplay Ability System (GAS), can be possessed by players or AI .
 */
UCLASS()
class CREATUREOASIS_API AGASPawn : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGASPawn();

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void InitializeAttributes();
	virtual void AddStartupEffects();
	virtual void GiveAbilities();
	
public:
	
	virtual void PossessedBy(AController* NewController) override;

	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	// Removes all CharacterAbilities
	virtual void RemoveCharacterAbilities();
	
	/**
	* Getters for attributes from AttributeSetBase
	**/
	UFUNCTION(BlueprintCallable, Category = "GAS")
	int32 GetCharacterLevel() const;
	
	UFUNCTION(BlueprintCallable, Category = "GAS")
	float GetHitpoints() const;

	// list of default gameplay abilities
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	TArray<TSubclassOf<class UBaseGameplayAbility>> CharacterAbilities;
	
	// Effect that initializes our default attributes
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

private:
	UPROPERTY()
	class UBaseAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	class UBaseAttributeSet* BaseAttributeSet;
};
