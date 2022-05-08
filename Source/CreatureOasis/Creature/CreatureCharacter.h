// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureOasis/GameplayAbilitySystem/GASCharacter.h"

#include "CreatureOasis/Components/ExpressionComponent.h"
#include "CreatureOasis/Components/EvolutionComponent.h"

#include "CreatureCharacter.generated.h"

class UManageEmotionComponent;
class UManageEvolutionComponent;

UCLASS()
class CREATUREOASIS_API ACreatureCharacter : public AGASCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACreatureCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBoxComponent* PickUpBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* PickUpAnchor;

	UPROPERTY(BlueprintReadOnly)
	UEvolutionComponent* EvolutionComponent;
	
	UPROPERTY(BlueprintReadOnly)
	UExpressionComponent* ExpressionComponent;
};
