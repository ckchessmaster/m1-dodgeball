// Fill out your copyright notice in the Description page of Project Settings.

#include "DodgeballGameMode.h"
#include "EngineUtils.h"
#include "DodgeballPlayerState.h"
#include "Engine.h"
#include "DodgeballPlayerController.h"
#include "BallActor.h"
#include "DodgeballGameInstance.h"

ADodgeballGameMode::ADodgeballGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bUseSeamlessTravel = true;
	
}

void ADodgeballGameMode::BeginPlay()
{
	Super::BeginPlay();

	// change this later
	ADodgeballGameState* gamestate = GetGameState<ADodgeballGameState>();
	gamestate->SetMatchState(EMatchState::MS_PreGame);

	//testing remove later----------------------------------------------------------------------------------------------------------------------
	Cast<UDodgeballGameInstance>(GetGameInstance())->SetNumPlayers(0);
	//testing remove later----------------------------------------------------------------------------------------------------------------------

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

AActor* ADodgeballGameMode::GetSpectatorSpawn()
{
	APlayerStart* SpectatorStart = nullptr;

	for (TActorIterator<APlayerStart> Itr(GetWorld()); Itr; ++Itr) {
		if (Itr->PlayerStartTag.Compare("0") == 0) {
			SpectatorStart = *Itr;
		}
	}

	return SpectatorStart;
}

void ADodgeballGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(gamestate->GetGameTime()));

	ADodgeballGameState* GameState = GetGameState<ADodgeballGameState>();

	switch (GetGameState<ADodgeballGameState>()->GetMatchState()) {
	case EMatchState::MS_PreGame: {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "The number of players is: " + FString::FromInt(GetNumPlayers()));
		if (GetWorld() != nullptr && GetNumPlayers() >= Cast<UDodgeballGameInstance>(GetGameInstance())->GetNumPlayers()) {
			// Make sure all players have fired BeginPlay()
			bool bCanStartGame = true;
			for (FConstPlayerControllerIterator Itr = GetWorld()->GetPlayerControllerIterator(); Itr; ++Itr) {
				if (!Cast<APlayerController>(Itr->Get())->Tags.Contains("Ready")) {
					bCanStartGame = false;
				}
			}//end player controller iterator
			if (bCanStartGame) {
				GameState->SetMatchState(EMatchState::MS_AbilitySelect);
			}
		}//end world check/player join check
	}//end MS_PreGame
		break;
	case EMatchState::MS_AbilitySelect: {
		if (GameState->GetGameTime() <= 0.f) {
			GameState->SetMatchState(EMatchState::MS_RoundBegin);
		} else {
			GameState->SetGameTime(GameState->GetGameTime() - DeltaTime);
		}
	}//end case MS_AbilitySelect
		break;
	case EMatchState::MS_RoundBegin: {
		if (GameState->GetGameTime() <= 0.f) {
			GameState->SetMatchState(EMatchState::MS_RoundInProgress);
		} else {
			GameState->SetGameTime(GameState->GetGameTime() - DeltaTime);
		}
	}//end case MS_RoundBegin
		break;
	case EMatchState::MS_RoundInProgress: {
		if (GameState->GetGameTime() <= 0.f) {
			GameState->SetMatchState(EMatchState::MS_SuddenDeath);
		} else {
			GameState->SetGameTime(GameState->GetGameTime() - DeltaTime);
		}
	}//end case MS_RoundInProgress
		break;
	case EMatchState::MS_SuddenDeath: {
		GameState->SetGameTime(GameState->GetGameTime() + DeltaTime);
	}//end case MS_SuddenDeath
		break;
	case EMatchState::MS_RoundEnd: {
		if (GameState->GetGameTime() <= 0.f) {
			if (GameState->GetCurrentRound() >= GameState->GetMaxRounds()) {
				GameState->SetMatchState(EMatchState::MS_GameEnd);
			} else {
				GameState->SetMatchState(EMatchState::MS_AbilitySelect);
			}// end end of game check
		} else {
			GameState->SetGameTime(GameState->GetGameTime() - DeltaTime);
		}
	}//end case MS_RoundEnd
		break;
	case EMatchState::MS_GameEnd: {
		if (GameState->GetGameTime() <= 0.f) {
			// Play again logic
			if (true) {
				GetWorld()->ServerTravel("Lobby");
			}//end play again check
		} else {
			GameState->SetGameTime(GameState->GetGameTime() - DeltaTime);
		}
	}//end case MS_GameEnd
		break;
	}//end switch
}

void ADodgeballGameMode::OnMatchStateChanged(EMatchState NewMatchState)
{
	ADodgeballGameState* GameState = GetGameState<ADodgeballGameState>();
	ADodgeballPlayerController* Player = Cast<ADodgeballPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	switch (NewMatchState) {
	case EMatchState::MS_PreGame:
		// do pregame stuff
		break;
	case EMatchState::MS_AbilitySelect: {
		Player->DisplayAbilitySelect();
		GameState->SetGameTime(GameState->AbilitySelectTime);
		break;
	case EMatchState::MS_RoundBegin:
		GameState->NewRound();
		SpawnPlayers();
		Player->DisplayHUD();
		GameState->SetGameTime(GameState->RoundBeginTime);
		break;
	case EMatchState::MS_RoundInProgress:
		GameState->SetGameTime(GameState->RoundInProgressTime);
		break;
	case EMatchState::MS_SuddenDeath: 
		GameState->SetGameTime(GameState->SuddenDeathTime);
		break;
	case EMatchState::MS_RoundEnd: 
		CleanupWorld();
		SpawnSpectators();
		Player->DisplayEndOfRound(1);
		GameState->SetGameTime(GameState->RoundEndTime);
	}//end case MS_RoundEnd
		break;
	case EMatchState::MS_GameEnd:
		Player->DisplayEndOfGame(1);
		GameState->SetGameTime(GameState->GameEndTime);
		break;
	}//end switch
}

void ADodgeballGameMode::SpawnPlayers()
{
	for (FConstPlayerControllerIterator Itr = GetWorld()->GetPlayerControllerIterator(); Itr; ++Itr) {
		APlayerController* Player = Itr->Get();

		AActor* Spawn = ChoosePlayerStart(Player);

		if (Spawn) {
			FVector Location = Spawn->GetActorLocation();
			FRotator Rotation = Spawn->GetActorRotation();
			FActorSpawnParameters SpawnInfo;
			ACharacter* NewCharacter = GetWorld()->SpawnActor<ACharacter>(DefaultPawnClass, Location, Rotation, SpawnInfo);

			if (NewCharacter) {
				Player->PlayerState->Tags.Remove("Dead");
				Player->Possess(NewCharacter);
			}//end NewCharacter null check
		}//end Spawn null check
	}//end player controller iteration
}

void ADodgeballGameMode::SpawnSpectators()
{
	for (FConstPlayerControllerIterator Itr = GetWorld()->GetPlayerControllerIterator(); Itr; ++Itr) {
		APlayerController* Player = Itr->Get();

		AActor* Spawn = GetSpectatorSpawn();

		if (Spawn) {
			FVector Location = Spawn->GetActorLocation();
			FRotator Rotation = Spawn->GetActorRotation();
			FActorSpawnParameters SpawnInfo;
			ASpectatorPawn* NewSpectator = GetWorld()->SpawnActor<ASpectatorPawn>(Location, Rotation, SpawnInfo);

			if (NewSpectator) {
				Player->Possess(NewSpectator);
			}//end NewCharacter null check
		}//end Spawn null check
	}//end player controller iteration
}

void ADodgeballGameMode::CleanupWorld()
{
	for (TActorIterator<ACharacter> Itr(GetWorld()); Itr; ++Itr) {
		Itr->Destroy();
	}

	for (TActorIterator<ABallActor> Itr(GetWorld()); Itr; ++Itr) {
		Itr->Destroy();
	}

	UsedStarts.Empty();
}

int ADodgeballGameMode::EndOfRoundCheck()
{
	ADodgeballGameState* gamestate = GetGameState<ADodgeballGameState>();
	
	TArray<APlayerState*> Team1;
	TArray<APlayerState*> Team2;

	for (APlayerState* Player : gamestate->PlayerArray) {
		if (!Player->Tags.Contains("Dead")) {
			if (Player->Tags.Contains("Team 1")) {
				Team1.Add(Player);
			} else if (Player->Tags.Contains("Team 2")) {
				Team2.Add(Player);
			}
		}
	}

	if (Team1.Num() == 0) {
		return 2;
	} else if (Team2.Num() == 0) {
		return 1;
	} else {
		return 0;
	}
	return 0;
}

void ADodgeballGameMode::OnPlayerDeath()
{
	if (int WinningTeam = EndOfRoundCheck() != 0) {
		ADodgeballGameState* GameState = GetGameState<ADodgeballGameState>();
		//FString Message = FString::Printf(TEXT("Team %d has won!"), WinningTeam);
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, Message);
		GameState->IncreaseScore(WinningTeam);
		
		GameState->SetMatchState(EMatchState::MS_RoundEnd);
	}
}
