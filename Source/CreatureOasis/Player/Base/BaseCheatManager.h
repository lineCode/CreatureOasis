﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "BaseCheatManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CREATUREOASIS_API UBaseCheatManager : public UCheatManager
{
	GENERATED_BODY()

protected:
	virtual void InitCheatManager() override;
};
