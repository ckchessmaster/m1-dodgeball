// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMenuPlayerController::BeginPlay() {
	Super::BeginPlay();

	if (wMainMenu && IsLocalController()) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		MainMenu = CreateWidget<UUserWidget>(this, wMainMenu);

		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (MainMenu)
		{
			//let add it to the view port
			MainMenu->AddToViewport();
		}

		//Show the Cursor.
		bShowMouseCursor = true;
	}
}


