#include "BaseGardenGameMode.h"

#include "CreatureOasis/Player/Base/BasePlayerController.h"

ABaseGardenGameMode::ABaseGardenGameMode()
{
	PlayerControllerClass = ABasePlayerController::StaticClass();
}

void ABaseGardenGameMode::BeginPlay()
{
	Super::BeginPlay();
}
