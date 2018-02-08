// Fill out your copyright notice in the Description page of Project Settings.

#include "DodgeballGameState.h"
#include "Net/UnrealNetwork.h"
#include "DodgeballGameMode.h"
#include "DodgeballPlayerController.h"
#include "Engine.h"

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
	DOREPLIFETIME(ADodgeballGameState, Team1Score);
	DOREPLIFETIME(ADodgeballGameState, Team2Score);
}

void ADodgeballGameState::OnRep_UpdateUI()
{
	ADodgeballPlayerController* Player = Cast<ADodgeballPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	switch (CurrentMatchState) {
	case EMatchState::MS_AbilitySelect:
		Player->DisplayAbilitySelect();
		break;
	case EMatchState::MS_RoundBegin:
		Player->DisplayHUD();
		break;
	case EMatchState::MS_RoundEnd: 
		Player->DisplayEndOfRound(1);
		break;
	case EMatchState::MS_GameEnd: 
		Player->DisplayEndOfGame(1);
		break;
	}//end switch
}

void ADodgeballGameState::SetMatchState(EMatchState NewMatchState)
{
	if (HasAuthority()) {
		PreviousMatchState = CurrentMatchState;
		CurrentMatchState = NewMatchState;

		Cast<ADodgeballGameMode>(AuthorityGameMode)->OnMatchStateChanged(NewMatchState);
	}
}

void ADodgeballGameState::IncreaseScore(int Team)
{
	switch (Team) {
	case 1:
		Team1Score = Team1Score++;
		break;
	case 2:
		Team2Score = Team2Score++;
		break;
	default:
		break;
	}
}