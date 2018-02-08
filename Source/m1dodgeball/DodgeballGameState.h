// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "GameFramework/GameStateBase.h"
#include "DodgeballGameState.generated.h"

UENUM(BlueprintType)
enum class EMatchState : uint8
{
	MS_Paused			UMETA(DisplayName = "Paused"),
	MS_PreGame			UMETA(DisplayName = "Pre Game"),
	MS_AbilitySelect	UMETA(DisplayName = "Ability Select"),
	MS_RoundBegin		UMETA(DisplayName = "Round Begin"),
	MS_RoundInProgress	UMETA(DisplayName = "Round In Progress"),
	MS_SuddenDeath		UMETA(DisplayName = "Sudden Death"),
	MS_RoundEnd			UMETA(DisplayName = "Round End"),
	MS_GameEnd			UMETA(DisplayName = "Game End")
};

UCLASS()
class M1DODGEBALL_API ADodgeballGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(Replicated)
	EMatchState CurrentMatchState;
	EMatchState PreviousMatchState;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	int CurrentRound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int MaxRounds;

	UPROPERTY(Replicated)
	float GameTime; // game time in seconds

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	int Team1Score;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
	int Team2Score;

public:
	ADodgeballGameState(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = "Match State")
	float AbilitySelectTime = 120.f;
	UPROPERTY(EditAnywhere, Category = "Match State")
	float RoundBeginTime = 5.f;
	UPROPERTY(EditAnywhere, Category = "Match State")
	float RoundInProgressTime = 420.f;
	UPROPERTY(EditAnywhere, Category = "Match State")
	float SuddenDeathTime = 0.f;
	UPROPERTY(EditAnywhere, Category = "Match State")
	float RoundEndTime = 10.f;
	UPROPERTY(EditAnywhere, Category = "Match State")
	float GameEndTime = 30.f;

	UFUNCTION(BlueprintCallable)
	void SetMatchState(EMatchState NewMatchState);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	EMatchState GetMatchState() { return CurrentMatchState; }
	EMatchState GetPreviousMatchState() { return PreviousMatchState; }

	UFUNCTION(BlueprintCallable)
	void SetGameTime(float NewTime) { GameTime = NewTime; }
	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetGameTime() { return GameTime; }
	
	UFUNCTION(BlueprintCallable)
	void NewRound() { CurrentRound++; }
	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetCurrentRound() { return CurrentRound; }
	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetMaxRounds() { return MaxRounds; }
	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetTeam1Score() { return Team1Score; }
	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetTeam2Score() { return Team2Score; }
	void IncreaseScore(int Team);
	
};
