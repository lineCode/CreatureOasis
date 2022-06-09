#include "BaseGardenGameMode.h"

#include "CreatureOasis/Characters/ThirdPersonCharacter/Base/BasePlayerController.h"

ABaseGardenGameMode::ABaseGardenGameMode()
{
	PlayerControllerClass = ABasePlayerController::StaticClass();
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/CreatureOasis/Core/Characters/ThirdPersonCharacter/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}