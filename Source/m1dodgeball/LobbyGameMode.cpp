// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"
#include "MenuPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "LobbyGameState.h"
#include "GameFramework/PlayerState.h"
#include "LobbyPlayerController.h"
#include "Engine.h"

ALobbyGameMode::ALobbyGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bUseSeamlessTravel = true;
}

APlayerController* ALobbyGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) {
	AMenuPlayerController* NewController = (AMenuPlayerController*)Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
	
	FString username = UGameplayStatics::ParseOption(Options, "Username");

	NewController->PlayerState->PlayerName = username;
	GetGameState<ALobbyGameState>()->MovePlayerToTeam(2, username);

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		ALobbyPlayerController* lpc = (ALobbyPlayerController*)Iterator->Get();
		lpc->UpdateLobby();
	}

	return NewController;
}

void ALobbyGameMode::StartGame() 
{
	GetWorld()->ServerTravel("DefaultMap");
}

