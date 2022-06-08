#include "BaseGardenGameMode.h"

#include "CreatureOasis/Characters/ThirdPersonCharacter/Base/BasePlayerController.h"
#include "CreatureOasis/Objects/GardenActorsManager.h"

ABaseGardenGameMode::ABaseGardenGameMode()
	: GardenActorsManager(NewObject<UGardenActorsManager>())
{
	PlayerControllerClass = ABasePlayerController::StaticClass();
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/CreatureOasis/Core/Characters/ThirdPersonCharacter/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

UGardenActorsManager* ABaseGardenGameMode::GetGardenActorsManager() const
{
	return GardenActorsManager;
}