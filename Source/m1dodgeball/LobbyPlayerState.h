// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LobbyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class M1DODGEBALL_API ALobbyPlayerState : public APlayerState
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Replicated)
	int Team;

public:
	ALobbyPlayerState(const FObjectInitializer& ObjectInitializer);
	virtual void SeamlessTravelTo(APlayerState* NewPlayerState) override;

	UFUNCTION(BlueprintPure)
	int GetTeam();

	UFUNCTION(BlueprintCallable)
	void SetTeam(int TeamNumber);
	
};
