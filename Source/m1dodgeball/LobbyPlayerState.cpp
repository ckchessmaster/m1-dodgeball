// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyPlayerState.h"
#include "Net/UnrealNetwork.h"

ALobbyPlayerState::ALobbyPlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Team = 2; //Set the initial team to spectator
}

void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(ALobbyPlayerState, Team);
}

void ALobbyPlayerState::SeamlessTravelTo(APlayerState* NewPlayerState)
{
	Super::SeamlessTravelTo(NewPlayerState);

	NewPlayerState->SetPlayerName(PlayerName);
	((ALobbyPlayerState*)NewPlayerState)->SetTeam(GetTeam());
}

int ALobbyPlayerState::GetTeam()
{
	return Team;
}

void ALobbyPlayerState::SetTeam(int TeamNumber)
{
	this->Team = TeamNumber;
}
