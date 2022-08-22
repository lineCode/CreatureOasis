// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUD.h"

ABaseHUD::ABaseHUD()
{
	GConfig->GetString(
	  TEXT("/Script/EngineSettings.GeneralProjectSettings"),
	  TEXT("ProjectVersion"),
	  AppVersion,
	  GGameIni
	);
	
	AppVersion = FString(__TIMESTAMP__);
}

void ABaseHUD::DrawHUD()
{
	Super::DrawHUD();

	FVector2D ViewportSize;
	GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);
	ViewportSize *= GetWorld()->GetGameViewport()->GetDPIScale();
	
	DrawText(AppVersion, FLinearColor(0.5f,0.5f,0.5f, 0.75f), ViewportSize.X - 100.f, ViewportSize.Y, nullptr, 0.95f, true);
}
