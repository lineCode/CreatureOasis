﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

/**
 * 
 */
UCLASS()
class CREATUREOASIS_API ABaseHUD : public AHUD
{
	GENERATED_BODY()

public:
	ABaseHUD();
	
	virtual void DrawHUD() override;

private:
	FString AppVersion;
};
