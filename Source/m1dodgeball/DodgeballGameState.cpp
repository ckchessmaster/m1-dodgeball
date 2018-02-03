// Fill out your copyright notice in the Description page of Project Settings.

#include "DodgeballGameState.h"
#include "Net/UnrealNetwork.h"

ADodgeballGameState::ADodgeballGameState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CurrentMatchState = EMatchState::MS_PreGame;
	PreviousMatchState = EMatchState::MS_PreGame;
}

void ADodgeballGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADodgeballGameState, CurrentMatchState);
	DOREPLIFETIME(ADodgeballGameState, GameTime);
}

void ADodgeballGameState::OnMatchStateChanged()
{
	OnMatchStateChangedBP();
}

void ADodgeballGameState::SetMatchState(EMatchState NewMatchState)
{
	PreviousMatchState = CurrentMatchState;
	CurrentMatchState = NewMatchState;

	OnMatchStateChanged();
}
