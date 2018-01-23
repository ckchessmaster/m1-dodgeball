// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "DodgeballGameMode.generated.h"

/**
 * 
 */
UCLASS()
class M1DODGEBALL_API ADodgeballGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	TArray<APlayerStart*> UsedStarts;

public:
	ADodgeballGameMode(const FObjectInitializer& ObjectInitializer);
	
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	
};
