// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuPlayerController.h"
#include "DodgeballPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class M1DODGEBALL_API ADodgeballPlayerController : public AMenuPlayerController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	UFUNCTION(Reliable, NetMulticast)
	void DisplayHUD();
	void DisplayHUD_Implementation();
	

	UFUNCTION(Reliable, NetMulticast)
	void DisplayAbilitySelect();
	void DisplayAbilitySelect_Implementation();
	

	UFUNCTION(Reliable, NetMulticast)
	void DisplayEndOfRound(int WinningTeam);
	void DisplayEndOfRound_Implementation(int WinningTeam);
	

	UFUNCTION(Reliable, NetMulticast)
	void DisplayEndOfGame(int WinningTeam);
	void DisplayEndOfGame_Implementation(int WinningTeam);
	
};
