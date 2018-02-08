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

	void SpawnPlayers();
	void SpawnSpectators();
	AActor* GetSpectatorSpawn();

	// Return 0 if round is not over otherwise return the team that has won
	virtual int EndOfRoundCheck();

protected:
	virtual void CleanupWorld();

public:
	ADodgeballGameMode(const FObjectInitializer& ObjectInitializer);
	
	virtual void BeginPlay() override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	virtual void Tick(float DeltaTime) override;

	virtual void OnMatchStateChanged(EMatchState NewMatchState);
	virtual void OnPlayerDeath();
};
