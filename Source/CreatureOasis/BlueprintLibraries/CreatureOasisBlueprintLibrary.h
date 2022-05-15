#pragma once

#include "CreatureOasisBlueprintLibrary.generated.h"

/*
 * Game-specific blueprint library
 * Used for exposing native code to blueprints
 */
UCLASS()
class CREATUREOASIS_API UCreatureOasisBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/* Show the loading screen. If bPlayUntilStopped is false, it will be displayed for PlayTime and automatically stop */
	UFUNCTION(BlueprintCallable, Category="LoadScreen")
	static void PlayLoadingScreen(bool bPlayUntilStopped, float PlayTime);

	/* Stops displaying the active loading screen. Can only be called if bPlayUntilStopped was true */
	UFUNCTION(BlueprintCallable, Category="LoadScreen")
	static void StopLoadingScreen();

	/* Generate random color */
	UFUNCTION(BlueprintCallable, Category="Colors")
	static FLinearColor GenerateRandomColor();
};
