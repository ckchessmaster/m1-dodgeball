// Fill out your copyright notice in the Description page of Project Settings.

#include "DodgeballGameMode.h"
#include "EngineUtils.h"
#include "DodgeballPlayerState.h"

ADodgeballGameMode::ADodgeballGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bUseSeamlessTravel = true;
}

AActor * ADodgeballGameMode::ChoosePlayerStart_Implementation(AController * Player)
{
	APlayerStart* spectatorStart = nullptr;

	for (TActorIterator<APlayerStart> Itr(GetWorld()); Itr; ++Itr) {
		APlayerStart* start = *Itr;

		ADodgeballPlayerState* player = (ADodgeballPlayerState*)Player->PlayerState;
		FName teamName = FName(*FString::FromInt(player->GetTeam()));

		//This is the spectator spawn
		if (teamName.Compare("0") == 0) {
			spectatorStart = start;
			continue;
		}

		// Check to see if there is a valid spawn on our team
		if (!UsedStarts.Contains(start) && start->PlayerStartTag.Compare(teamName) == 0) {
			UsedStarts.Add(start);
			return start;
		}
	}

	// No valid spawns left so player must be a spectator
	return spectatorStart;
}
