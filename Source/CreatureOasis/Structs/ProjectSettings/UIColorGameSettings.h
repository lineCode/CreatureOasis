// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIColorGameSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, defaultconfig, meta = (DisplayName="Color Game Settings"))
class CREATUREOASIS_API UUIColorGameSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	int32 TestInt;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	TMap<FString, FColor> DummyColorAccents;
};
