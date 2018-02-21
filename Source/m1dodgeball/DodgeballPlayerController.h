// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuPlayerController.h"
#include "DodgeballGameplayAbility.h"
#include "DodgeballPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class M1DODGEBALL_API ADodgeballPlayerController : public AMenuPlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UDodgeballGameplayAbility> AbilityClass;
	
public:

	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void SelectAbility(TSubclassOf<UDodgeballGameplayAbility> NewAbilityClass);
	void SelectAbility_Implementation(TSubclassOf<UDodgeballGameplayAbility> NewAbilityClass);
	bool SelectAbility_Validate(TSubclassOf<UDodgeballGameplayAbility> NewAbilityClass);

	void DisplayHUD();
	void DisplayAbilitySelect();
	void DisplayEndOfRound(int WinningTeam);
	void DisplayEndOfGame(int WinningTeam);

	TSubclassOf<UDodgeballGameplayAbility> GetAbilityClass() { return AbilityClass; }
};
