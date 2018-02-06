// Fill out your copyright notice in the Description page of Project Settings.

#include "DodgeballGameState.h"
#include "Net/UnrealNetwork.h"
#include "DodgeballGameMode.h"

ADodgeballGameState::ADodgeballGameState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CurrentMatchState = EMatchState::MS_PreGame;
	PreviousMatchState = EMatchState::MS_PreGame;
	CurrentRound = 0;
	MaxRounds = 3;
}

void ADodgeballGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADodgeballGameState, CurrentMatchState);
	DOREPLIFETIME(ADodgeballGameState, GameTime);
	DOREPLIFETIME(ADodgeballGameState, CurrentRound);
}

void ADodgeballGameState::SetMatchState(EMatchState NewMatchState)
{
	if (HasAuthority()) {
		PreviousMatchState = CurrentMatchState;
		CurrentMatchState = NewMatchState;

		Cast<ADodgeballGameMode>(AuthorityGameMode)->OnMatchStateChanged(NewMatchState);
	}
}
