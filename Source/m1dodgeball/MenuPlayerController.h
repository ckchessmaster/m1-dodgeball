// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class M1DODGEBALL_API AMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
private:


public:
	// Reference UMG Asset in the Editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> wMainMenu;
	
	// Variable to hold the widget after creating it
	UUserWidget* MainMenu;

	// Override BeingPlay()
	virtual void BeginPlay() override;
};
