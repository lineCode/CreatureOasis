#pragma once

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"

#include "CreatureOasisBlueprintLibrary.generated.h"

class UAbilitySystemComponent;

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

	/* Converts a world location to screen position for HUD drawing. This differs from the results of FSceneView::WorldToScreen in that it returns a position along the edge of the screen for offscreen locations
		*
		* @param		InLocation	- The world space location to be converted to screen space
		* @param		EdgePercent - How close to the edge of the screen, 1.0 = at edge, 0.0 = at center of screen. .9 or .95 is usually desirable
		* @outparam	OutScreenPosition - the screen coordinates for HUD drawing
		* @outparam	OutRotationAngleDegrees - The angle to rotate a hud element if you want it pointing toward the offscreen indicator, 0 if onscreen */
	UFUNCTION(BlueprintPure, meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext), Category="HUD|Util")
	static void FindScreenEdgeLocationForWorldLocation(const UObject* WorldContextObject, const FVector& InLocation, const float EdgePercent,  FVector2D& OutScreenPosition, float& OutRotationAngleDegrees, bool& bIsOnScreen);

	UFUNCTION(BlueprintCallable, Category="GameplayTagManager")
	static bool GetDirectActiveChildTag(UAbilitySystemComponent* ASC, FGameplayTag ParentTag, FGameplayTag& OutGameplayTag);

	UFUNCTION(BlueprintCallable, Category="GameplayTagManager")
	static bool GetNameOfTopMostChildTag(const FGameplayTag& TargetTag, FName& OutName);

	UFUNCTION(BlueprintCallable, Category="GameplayTagManager")
	static bool GetRandomTagFromGameplayTagContainer(const FGameplayTagContainer InTagContainer, FGameplayTag& OutTag);

	UFUNCTION(BlueprintCallable, Category="GameplayTagManager")
	static FGameplayTag GetTypeTagAssignedToAbilitySystemComponent(UAbilitySystemComponent* AbilitySystemComponent);

	UFUNCTION(BlueprintCallable, Category="GameplayTagManager")
	static FGameplayTag RequestGameplayTagFromName(const FName InTagName);
	
	// Debug methods
	
	// Force sets an attribute to specific value, shouldn't be used in regular gameplay
	// Sets the base value of an attribute. Existing active modifiers are NOT cleared and will act upon the new base value.
	UFUNCTION(BlueprintCallable, Category="GAS Debugging")
	static void SetAttributeBaseInAbilitySystemComponent(const FGameplayAttribute& TargetAttribute, const float NewValue, UAbilitySystemComponent* AbilitySystemComponent);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="GAS Debuggin")
	static FString GetNameOfGameplayAttribute(const FGameplayAttribute& TargetAttribute);
};
