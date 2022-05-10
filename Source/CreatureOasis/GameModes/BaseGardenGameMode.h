#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BaseGardenGameMode.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CREATUREOASIS_API ABaseGardenGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABaseGardenGameMode();
	
protected:
	virtual void BeginPlay() override;
};
