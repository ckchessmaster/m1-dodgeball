// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyPlayerController.h"
#include "LobbyUserWidget.h"
#include "Engine.h"
#include "LobbyGameState.h"
#include "LobbyGameMode.h"
#include "LobbyPlayerState.h"

void ALobbyPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	UpdateLobby();
}

void ALobbyPlayerController::UpdateLobby()
{
	if (MainMenu) {
		((ULobbyUserWidget*)MainMenu)->UpdateLobbyBP();
	}
}

bool ALobbyPlayerController::ChangeTeam_Validate(int Team, const FString& Username)
{
	return true;
}

void ALobbyPlayerController::ChangeTeam_Implementation(int Team, const FString& Username)
{
	if (Role == ROLE_Authority) {
		GetWorld()->GetAuthGameMode()->GetGameState<ALobbyGameState>()->MovePlayerToTeam(Team, Username);
		((ALobbyPlayerState*)PlayerState)->SetTeam(Team);
	}
}

// SeamlessTravelTo
void ALobbyPlayerController::StartGame_Implementation()
{
	if (Role == ROLE_Authority) {
		((ALobbyGameMode*)GetWorld()->GetAuthGameMode())->StartGame();
	}
}

bool ALobbyPlayerController::StartGame_Validate()
{
	//Eventually check if player is actually the host
	return true;
}
