// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "DodgeballGameState.h"
#include "DodgeballGameMode.generated.h"

/**
 * 
 */
UCLASS()
class M1DODGEBALL_API ADodgeballGameMode : public AGameModeBase
{
	GENERATED_BODY()

	TArray<APlayerStart*> UsedStarts;

	int NumTravelingPlayers;

	void SpawnPlayers();
	void SpawnSpectators();
	AActor* GetSpectatorSpawn();
	int WinningTeam;

	// Return 0 if round is not over otherwise return the team that has won
	virtual int EndOfRoundCheck();

protected:
	virtual void CleanupWorld();

public:
	ADodgeballGameMode(const FObjectInitializer& ObjectInitializer);
	
	virtual void BeginPlay() override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
	void OnMatchStateChanged(EMatchState NewMatchState);

	virtual void OnPlayerDeath();
};

/* The following is a list of tags that are used throughout the game and their meaning:
Player Tags:
	Team 1/Team 2: The team a player belongs to
	Dead: The player is currently dead
	Immune: The player cannot take damage
Ability Tags:
	DefaultAttack: Used to denote the ability that is the basic throw ability
	Ability: Used to denote the ability that is a players secondary ability
 */