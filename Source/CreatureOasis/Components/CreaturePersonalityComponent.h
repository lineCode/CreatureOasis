// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CreatureOasis/Interfaces/CreatureComponentLoadableInterface.h"
#include "CreaturePersonalityComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CREATUREOASIS_API UCreaturePersonalityComponent : public UActorComponent, public ICreatureComponentLoadableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCreaturePersonalityComponent();
	
	UFUNCTION(BlueprintCallable)
	void SetCreatureName(FName NewNameString);

	UFUNCTION(BlueprintCallable)
	FName GetCreatureName() const;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void LoadCreatureData_Implementation(const FCreatureDataLoad& CreatureDataLoad) override;
	virtual void GatherCreatureData_Implementation(FCreatureDataLoad& CreatureDataLoad) override;
		
private:
	FName CreatureName;

	FGuid UniqueIdentifier;
};
