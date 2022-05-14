#include "BaseGardenGameMode.h"

#include "CreatureOasis/Characters/ThirdPersonCharacter/Base/BaseThirdPersonCharacter.h"

ABaseGardenGameMode::ABaseGardenGameMode()
{
	PlayerControllerClass = ABaseThirdPersonCharacter::StaticClass();
}

void ABaseGardenGameMode::BeginPlay()
{
	Super::BeginPlay();
}
