// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LobbyPlayerState.h"
#include "DodgeballPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class M1DODGEBALL_API ADodgeballPlayerState : public ALobbyPlayerState
{
	GENERATED_BODY()

protected:

public:
	virtual void BeginPlay() override;
	virtual void SeamlessTravelTo(APlayerState* NewPlayerState) override;
};
