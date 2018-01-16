// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MainMenuPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class M1DODGEBALL_API AMainMenuPlayerState : public APlayerState
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void SetPlayerName(FString Name);
	
	
	
};
