#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BaseGardenGameMode.generated.h"

class UGardenActorsManager;

/**
 * 
 */
UCLASS(Blueprintable)
class CREATUREOASIS_API ABaseGardenGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABaseGardenGameMode();

	UFUNCTION(BlueprintCallable)
	UGardenActorsManager* GetGardenActorsManager() const;
	
protected:
	UPROPERTY()
	UGardenActorsManager* GardenActorsManager;
};
