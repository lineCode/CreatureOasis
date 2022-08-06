#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "HoldableAnchorInterface.generated.h"

UINTERFACE()
class UHoldableAnchorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Given to those that are able to "Hold" an object and have the HoldableAnchorComponent assigned to them
 */
class CREATUREOASIS_API IHoldableAnchorInterface
{
	GENERATED_BODY()
	
public:
	/* Get the Actor that is being held by the active HoldableAnchorComponent assigned to this object */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=HoldableAnchorInterface)
	AActor* GetHeldActorFromHoldableAnchorComponent();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=HoldableAnchorInterface)
	bool IsHoldingActor();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=HoldableAnchorInterface)
	FGameplayTag GetTypeOfActorBeingHeld();
};
