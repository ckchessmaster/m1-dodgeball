// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "m1dodgeballGameMode.h"
#include "m1dodgeballHUD.h"
#include "m1dodgeballCharacter.h"
#include "UObject/ConstructorHelpers.h"

Am1dodgeballGameMode::Am1dodgeballGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = Am1dodgeballHUD::StaticClass();
}
