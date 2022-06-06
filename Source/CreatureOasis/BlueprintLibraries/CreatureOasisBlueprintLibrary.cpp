#include "CreatureOasisBlueprintLibrary.h"

#include "CreatureOasisLoadingScreen/CreatureOasisLoadingScreen.h"

void UCreatureOasisBlueprintLibrary::PlayLoadingScreen(bool bPlayUntilStopped, float PlayTime)
{
	FCreatureOasisLoadingScreenModule& LoadingScreenModule = FCreatureOasisLoadingScreenModule::Get();
	LoadingScreenModule.StartInGameLoadingScreen(bPlayUntilStopped, PlayTime);
}

void UCreatureOasisBlueprintLibrary::StopLoadingScreen()
{
	FCreatureOasisLoadingScreenModule& LoadingScreenModule = FCreatureOasisLoadingScreenModule::Get();
	LoadingScreenModule.StopInGameLoadingScreen();
}

FLinearColor UCreatureOasisBlueprintLibrary::GenerateRandomColor()
{
	return {FMath::RandRange(0.f, 1.f), FMath::RandRange(0.f, 1.f), FMath::RandRange(0.f, 1.f), 1.f};
}

ABaseGardenGameMode* UCreatureOasisBlueprintLibrary::GetGardenGameMode(const UObject* WorldContextObject)
{
	const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	return Cast<ABaseGardenGameMode>(World->GetAuthGameMode());
}