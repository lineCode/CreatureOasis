#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HoldableInterface.generated.h"

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
	void StartBeingHold(AActor* ActorInstigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Trigger)
	void EndBeingHold();
};
