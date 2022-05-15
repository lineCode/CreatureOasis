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
	bool StartHold(AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Trigger)
	bool EndHold();
};
