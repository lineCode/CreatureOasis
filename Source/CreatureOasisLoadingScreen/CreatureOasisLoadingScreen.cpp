#include "CreatureOasisLoadingScreen.h"

#include "Widget/DefaultWidgetLoadingScreen.h"

#include "MoviePlayer.h"

void FCreatureOasisLoadingScreenModule::StartupModule()
{
	if (IsMoviePlayerEnabled())
	{
		CreateScreen();
	}
}

bool FCreatureOasisLoadingScreenModule::IsGameModule() const
{
	return true;
}

void FCreatureOasisLoadingScreenModule::StartInGameLoadingScreen(bool bPlayUntilStopped, float PlayTime)
{
	FLoadingScreenAttributes LoadingScreenAttributes;
	LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = !bPlayUntilStopped;
	LoadingScreenAttributes.bWaitForManualStop = bPlayUntilStopped;
	LoadingScreenAttributes.bAllowEngineTick = bPlayUntilStopped;
	LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = PlayTime;
	LoadingScreenAttributes.WidgetLoadingScreen = SNew(SDefaultWidgetLoadingScreen);
	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
}

void FCreatureOasisLoadingScreenModule::StopInGameLoadingScreen()
{
	GetMoviePlayer()->StopMovie();
}

void FCreatureOasisLoadingScreenModule::CreateScreen()
{
	FLoadingScreenAttributes LoadingScreenAttributes;
	LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = false;
	LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = 3.f;
	LoadingScreenAttributes.WidgetLoadingScreen = SNew(SDefaultWidgetLoadingScreen);
	
	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
}

IMPLEMENT_GAME_MODULE(FCreatureOasisLoadingScreenModule, CreatureOasisLoadingScreen);
