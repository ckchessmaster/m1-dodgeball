// Fill out your copyright notice in the Description page of Project Settings.

#include "DodgeballPlayerController.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "DodgeballCharacter.h"
#include "Camera/CameraComponent.h"
#include "DodgeballUserWidget.h"

void ADodgeballPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());
}

void ADodgeballPlayerController::DisplayHUD_Implementation()
{
	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());
	if (MainMenu) {
		Cast<UDodgeballUserWidget>(MainMenu)->DisplayHUDBP();
	}
}

void ADodgeballPlayerController::DisplayAbilitySelect_Implementation()
{
	bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());
	if (MainMenu) {
		Cast<UDodgeballUserWidget>(MainMenu)->DisplayAbilitySelectBP();
	}
}

void ADodgeballPlayerController::DisplayEndOfRound_Implementation(int WinningTeam)
{
	bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());
	if (MainMenu) {
		Cast<UDodgeballUserWidget>(MainMenu)->DisplayEndOfRoundBP(WinningTeam);
	}
}

void ADodgeballPlayerController::DisplayEndOfGame_Implementation(int WinningTeam)
{
	bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());
	if (MainMenu) {
		Cast<UDodgeballUserWidget>(MainMenu)->DisplayEndOfGameBP(WinningTeam);
	}
	
}
