// Fill out your copyright notice in the Description page of Project Settings.

#include "DodgeballGameMode.h"
#include "EngineUtils.h"
#include "DodgeballPlayerState.h"
#include "DodgeballGameState.h"
#include "Engine.h"

ADodgeballGameMode::ADodgeballGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bUseSeamlessTravel = true;
	
}

void ADodgeballGameMode::BeginPlay()
{
	Super::BeginPlay();

	// change this later
	ADodgeballGameState* gamestate = GetGameState<ADodgeballGameState>();
	gamestate->SetMatchState(EMatchState::MS_AbilitySelect);
	gamestate->SetGameTime(gamestate->AbilitySelectTime);
}

AActor * ADodgeballGameMode::ChoosePlayerStart_Implementation(AController * Player)
{
	APlayerStart* spectatorStart = nullptr;

	for (TActorIterator<APlayerStart> Itr(GetWorld()); Itr; ++Itr) {
		APlayerStart* start = *Itr;

		ADodgeballPlayerState* player = (ADodgeballPlayerState*)Player->PlayerState;
		FName teamName = FName(*FString::FromInt(player->GetTeam()));
		ADodgeballGameState* gamestate = GetGameState<ADodgeballGameState>();
		// Game hasn't started yet so spawn everyone at the spectator spawn
		if (gamestate->GetMatchState() == EMatchState::MS_PreGame || gamestate->GetMatchState() == EMatchState::MS_AbilitySelect) {
			if (start->PlayerStartTag.Compare("0") == 0) {
				return start;
			} else {
				continue;
			}
		} else {

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
		}// end if/else
	}// end loop

	// No valid spawns left so player must be a spectator
	return spectatorStart;
}

void ADodgeballGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ADodgeballGameState* gamestate = GetGameState<ADodgeballGameState>();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(gamestate->GetGameTime()));

	switch (GetGameState<ADodgeballGameState>()->GetMatchState()) {
	case EMatchState::MS_PreGame:
		break;
	case EMatchState::MS_AbilitySelect:
		if (gamestate->GetGameTime() <= 0.f) {
			gamestate->SetMatchState(EMatchState::MS_RoundBegin);
			SpawnPlayers();
			gamestate->SetGameTime(gamestate->RoundBeginTime);
		} else {
			gamestate->SetGameTime(gamestate->GetGameTime() - DeltaTime);
		}// end if/else
		break;
	case EMatchState::MS_RoundBegin:
		if (gamestate->GetGameTime() <= 0.f) {
			gamestate->SetMatchState(EMatchState::MS_RoundInProgress);
			gamestate->SetGameTime(gamestate->RoundInProgressTime);
		} else {
			gamestate->SetGameTime(gamestate->GetGameTime() - DeltaTime);
		}// end if/else
		break;
	case EMatchState::MS_RoundInProgress:
		if (gamestate->GetGameTime() <= 0.f) {
			gamestate->SetMatchState(EMatchState::MS_SuddenDeath);
			gamestate->SetGameTime(gamestate->SuddenDeathTime);
		} else {
			gamestate->SetGameTime(gamestate->GetGameTime() - DeltaTime);
		}// end if/else
		break;
	case EMatchState::MS_SuddenDeath:
		if (false) {
			gamestate->SetMatchState(EMatchState::MS_RoundEnd);
			gamestate->SetGameTime(gamestate->RoundEndTime);
		} else {
			gamestate->SetGameTime(gamestate->GetGameTime() + DeltaTime);
		}// end if/else
		break;
	case EMatchState::MS_RoundEnd:
		if (false) {
			gamestate->SetMatchState(EMatchState::MS_AbilitySelect);
			gamestate->SetGameTime(gamestate->AbilitySelectTime);
		}
		else {
			gamestate->SetGameTime(gamestate->GetGameTime() - DeltaTime);
		}// end if/else
		break;
	}
}

void ADodgeballGameMode::SpawnPlayers()
{

}
