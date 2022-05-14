// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerController.generated.h"

UCLASS()
class CREATUREOASIS_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasePlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
