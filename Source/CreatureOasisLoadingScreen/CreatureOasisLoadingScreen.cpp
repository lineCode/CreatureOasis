#include "CreatureOasisLoadingScreen.h"

#include "Widget/DefaultWidgetLoadingScreen.h"

#include "MoviePlayer.h"

void FCreatureOasisLoadingScreen::StartupModule()
{
	if (IsMoviePlayerEnabled())
	{
		CreateScreen();
	}
}

bool FCreatureOasisLoadingScreen::IsGameModule() const
{
	return true;
}

void FCreatureOasisLoadingScreen::StartInGameLoadingScreen(bool bPlayUntilStopped, float PlayTime)
{
	FLoadingScreenAttributes LoadingScreenAttributes;
	LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = !bPlayUntilStopped;
	LoadingScreenAttributes.bWaitForManualStop = bPlayUntilStopped;
	LoadingScreenAttributes.bAllowEngineTick = bPlayUntilStopped;
	LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = PlayTime;
	LoadingScreenAttributes.WidgetLoadingScreen = SNew(SDefaultWidgetLoadingScreen);
	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
}

void FCreatureOasisLoadingScreen::StopInGameLoadingScreen()
{
	GetMoviePlayer()->StopMovie();
}

void FCreatureOasisLoadingScreen::CreateScreen()
{
	FLoadingScreenAttributes LoadingScreenAttributes;
	LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = true;
	LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = 3.f;
	LoadingScreenAttributes.WidgetLoadingScreen = SNew(SDefaultWidgetLoadingScreen);
	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
}

IMPLEMENT_GAME_MODULE(FCreatureOasisLoadingScreen, Zephyr_DemoLoadingScreen);
