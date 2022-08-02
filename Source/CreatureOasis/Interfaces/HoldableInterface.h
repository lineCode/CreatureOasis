#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HoldableInterface.generated.h"

class AGASCharacter;

UINTERFACE()
class UHoldableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CREATUREOASIS_API IHoldableInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Trigger)
	void StartBeingHold(AGASCharacter* CharacterInstigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Trigger)
	void EndBeingHold();

	/* Returns nullptr if no Actor is currently holding us */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Trigger)
	AGASCharacter* GetCharacterCurrentlyHoldingUs();
};
