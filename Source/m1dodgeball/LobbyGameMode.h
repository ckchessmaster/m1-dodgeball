// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class M1DODGEBALL_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:

	
public:
	ALobbyGameMode(const FObjectInitializer& ObjectInitializer);
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	
	void StartGame();
};
