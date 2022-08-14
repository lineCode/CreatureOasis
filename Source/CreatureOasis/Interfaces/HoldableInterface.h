#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTags.h"
#include "HoldableInterface.generated.h"

class AGASCharacter;

UINTERFACE()
class UHoldableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Implemented by Actors that can be "Held" by other actors using the HoldableAnchorComponent
 */
class CREATUREOASIS_API IHoldableInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=HoldableInterface)
	void StartBeingHold(AGASCharacter* CharacterInstigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=HoldableInterface)
	void EndBeingHold();

	/* Returns nullptr if no Actor is currently holding us */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=HoldableInterface)
	AGASCharacter* GetCharacterCurrentlyHoldingUs();

	/* Get the objects gameplay tag type */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=HoldableInterface)
	FGameplayTag GetTypeOfActor();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=HoldableInterface)
	bool IsBeingHeld();
};
