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

	Tags.Add("Ready");
}

void ADodgeballPlayerController::SelectAbility_Implementation(TSubclassOf<UDodgeballGameplayAbility> NewAbilityClass)
{
	if (HasAuthority()) {
		AbilityClass = NewAbilityClass;
	}
}

bool ADodgeballPlayerController::SelectAbility_Validate(TSubclassOf<UDodgeballGameplayAbility> NewAbilityClass)
{
	return true;
}

void ADodgeballPlayerController::DisplayHUD()
{
	if (IsLocalController()) {
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
		if (MainMenu) {
			Cast<UDodgeballUserWidget>(MainMenu)->DisplayHUDBP();
		}
	}
}

void ADodgeballPlayerController::DisplayAbilitySelect()
{
	if (IsLocalController()) {
		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());
		if (MainMenu) {
			Cast<UDodgeballUserWidget>(MainMenu)->DisplayAbilitySelectBP();
		}
	}
}

void ADodgeballPlayerController::DisplayEndOfRound(int WinningTeam)
{
	if (IsLocalController()) {
		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());
		if (MainMenu) {
			Cast<UDodgeballUserWidget>(MainMenu)->DisplayEndOfRoundBP(WinningTeam);
		}
	}
}

void ADodgeballPlayerController::DisplayEndOfGame(int WinningTeam)
{
	if (IsLocalController()) {
		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());
		if (MainMenu) {
			Cast<UDodgeballUserWidget>(MainMenu)->DisplayEndOfGameBP(WinningTeam);
		}
	}
}
