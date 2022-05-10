#include "BaseCheatManager.h"

#include "HAL/IConsoleManager.h"

static FAutoConsoleCommand CustomCommand
{
	/*Name*/TEXT("/CustomCommand"),
	/*Info*/TEXT("A custom command that prints hello world!"),
	/*Func*/FConsoleCommandDelegate::CreateLambda([] () { UE_LOG(LogTemp, Display, TEXT("Hello World!")) })
};

void UBaseCheatManager::InitCheatManager()
{
	Super::InitCheatManager();
}