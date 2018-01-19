// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LobbyGameState.generated.h"

/**
 * 
 */
UCLASS()
class M1DODGEBALL_API ALobbyGameState : public AGameStateBase
{
	GENERATED_BODY()
private:
	UFUNCTION()
	void OnRep_UpdateLobby();

	UPROPERTY(ReplicatedUsing = OnRep_UpdateLobby)
	TArray<FString> Team1;
	UPROPERTY(ReplicatedUsing = OnRep_UpdateLobby)
	TArray<FString> Team2;
	UPROPERTY(ReplicatedUsing = OnRep_UpdateLobby)
	TArray<FString> Spectators;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintPure, Category = "Data")
	TArray<FString> GetTeam(int Team);

	void MovePlayerToTeam(int Team, FString Username);
	
	
	
};
