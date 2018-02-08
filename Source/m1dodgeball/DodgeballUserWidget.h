// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DodgeballUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class M1DODGEBALL_API UDodgeballUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void DisplayHUDBP();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void DisplayAbilitySelectBP();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void DisplayEndOfRoundBP(int WinningTeam);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void DisplayEndOfGameBP(int WinningTeam);
};
