#include "BaseGardenGameMode.h"

#include "CreatureOasis/Characters/ThirdPersonCharacter/Base/BasePlayerController.h"
#include "CreatureOasis/Objects/GardenDynamicObjectsManager.h"

ABaseGardenGameMode::ABaseGardenGameMode()
	: GardenDynamicObjectsManager(NewObject<UGardenDynamicObjectsManager>())
{
	PlayerControllerClass = ABasePlayerController::StaticClass();
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/CreatureOasis/Core/Characters/ThirdPersonCharacter/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ABaseGardenGameMode::BeginPlay()
{
	Super::BeginPlay();

	GardenDynamicObjectsManager->Initialize();
}

void ABaseGardenGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GardenDynamicObjectsManager->Uninitialize();
}
