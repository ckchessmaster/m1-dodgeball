// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuPlayerController.h"
#include "LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class M1DODGEBALL_API ALobbyPlayerController : public AMenuPlayerController
{
	GENERATED_BODY()
protected:
	

public:
	
	virtual void BeginPlay() override;
	virtual void PreClientTravel(const FString & PendingURL, ETravelType TravelType, bool bIsSeamlessTravel) override;

	void UpdateLobby();
	
	UFUNCTION(Reliable, Server, WithValidation, BlueprintCallable)
	void ChangeTeam(int Team, const FString& Username);
	void ChangeTeam_Implementation(int Team, const FString& Username);
	bool ChangeTeam_Validate(int Team, const FString& Username);

	UFUNCTION(Reliable, Server, WithValidation, BlueprintCallable)
	void StartGame();
	void StartGame_Implementation();
	bool StartGame_Validate();
};
