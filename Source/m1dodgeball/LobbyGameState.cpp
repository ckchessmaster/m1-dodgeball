// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameState.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "LobbyPlayerController.h"

void ALobbyGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(ALobbyGameState, Team1);
	DOREPLIFETIME(ALobbyGameState, Team2);
	DOREPLIFETIME(ALobbyGameState, Spectators);
}

TArray<FString> ALobbyGameState::GetTeam(int Team)
{
	switch (Team) {
	case 0:
		return Team1;
	case 1:
		return Team2;
	case 2:
		return Spectators;
	default:
		return TArray<FString>();
	}
}

void ALobbyGameState::MovePlayerToTeam(int Team, FString Username)
{
	// Remove player from any team they might already be on
	Team1.Remove(Username);
	Team2.Remove(Username);
	Spectators.Remove(Username);

	// Add player to a team
	switch (Team) {
	case 0:
		Team1.Add(Username);
		break;
	case 1:
		Team2.Add(Username);
		break;
	case 2:
		Spectators.Add(Username);
		break;
	default:
		break;
	}

	if (Role == ROLE_Authority) {
		ALobbyPlayerController* lpc = (ALobbyPlayerController*)UGameplayStatics::GetPlayerController(GetWorld(), 0);
		lpc->UpdateLobby();
	}
}

void ALobbyGameState::OnRep_UpdateLobby() 
{
	ALobbyPlayerController* lpc = (ALobbyPlayerController*)UGameplayStatics::GetPlayerController(GetWorld(), 0);
	lpc->UpdateLobby();
}
