// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DodgeballCharacter.generated.h"

UCLASS()
class M1DODGEBALL_API ADodgeballCharacter : public ACharacter
{
	GENERATED_BODY()

private:


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** First person camera */
	UPROPERTY(EditAnywhere, Category = Camera)
	class UCameraComponent* FirstPersonCameraComponent;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, Category = Camera)
	float BaseLookUpRate;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ABallActor> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, Category = Gameplay)
	class USoundBase* FireSound;

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/** Fires a projectile. */
	void OnFire();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

public:	
	// Sets default values for this character's properties
	ADodgeballCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	
};
