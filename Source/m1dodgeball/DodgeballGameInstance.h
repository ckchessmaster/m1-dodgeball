// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DodgeballGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class M1DODGEBALL_API UDodgeballGameInstance : public UGameInstance
{
	GENERATED_BODY()


	int NumPlayers;

public:

	int GetNumPlayers() { return NumPlayers; }
	void SetNumPlayers(int Num) { NumPlayers = Num; }
	
};
