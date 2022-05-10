// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"

#include "BaseCheatManager.h"


// Sets default values
ABasePlayerController::ABasePlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CheatManager = CreateDefaultSubobject<UBaseCheatManager>(TEXT("BaseCheatManager"));
}

// Called when the game starts or when spawned
void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
}