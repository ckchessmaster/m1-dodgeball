// Fill out your copyright notice in the Description page of Project Settings.

#include "DodgeballPlayerController.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "DodgeballCharacter.h"
#include "Camera/CameraComponent.h"

void ADodgeballPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = false;
}
