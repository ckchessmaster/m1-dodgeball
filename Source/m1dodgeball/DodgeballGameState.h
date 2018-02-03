// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DodgeballGameState.generated.h"

UENUM(BlueprintType)
enum class EMatchState : uint8
{
	MS_PreGame			UMETA(DisplayName = "Pre Game"),
	MS_AbilitySelect	UMETA(DisplayName = "Ability Select"),
	MS_RoundBegin		UMETA(DisplayName = "Round Begin"),
	MS_RoundInProgress	UMETA(DisplayName = "Round In Progress"),
	MS_SuddenDeath		UMETA(DisplayName = "Sudden Death"),
	MS_RoundEnd			UMETA(DisplayName = "Round End"),
	MS_GameEnd			UMETA(DisplayName = "Game End"),
	MS_Paused			UMETA(DisplayName = "Paused"),
};

UCLASS()
class M1DODGEBALL_API ADodgeballGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(ReplicatedUsing = OnMatchStateChanged)
	EMatchState CurrentMatchState;
	EMatchState PreviousMatchState;

	UPROPERTY(Replicated)
	float GameTime; // game time in seconds

	UFUNCTION()
	void OnMatchStateChanged();
	
	UFUNCTION(BlueprintCosmetic, BlueprintImplementableEvent)
	void OnMatchStateChangedBP();

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

	UFUNCTION(BlueprintCallable)
	void SetGameTime(float NewTime) { GameTime = NewTime; }
	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetGameTime() { return GameTime; }
	
	
	
};
