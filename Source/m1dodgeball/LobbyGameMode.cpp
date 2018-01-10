// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"
#include "MenuPlayerController.h"
#include "Kismet/GameplayStatics.h"

APlayerController* ALobbyGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) {
	AMenuPlayerController* NewController = (AMenuPlayerController*)Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
	
	NewController->SetUsername(UGameplayStatics::ParseOption(Options, "Username"));

	return NewController;
}



