// Fill out your copyright notice in the Description page of Project Settings.

#include "DodgeballPlayerState.h"

void ADodgeballPlayerState::BeginPlay()
{
	int test = GetTeam();
}

void ADodgeballPlayerState::SeamlessTravelTo(APlayerState* NewPlayerState)
{
	Super::SeamlessTravelTo(NewPlayerState);

	NewPlayerState->SetPlayerName(PlayerName);
	((ALobbyPlayerState*)NewPlayerState)->SetTeam(GetTeam());

	// Move everything over to a tag system in the future
	Tags.Add("Team " + GetTeam());
}