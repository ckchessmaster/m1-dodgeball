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
};
