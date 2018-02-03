// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h" 
#include "DodgeballCharacter.generated.h"

UENUM(BlueprintType)
enum class AbilityType : uint8
{
	ThrowBall UMETA(DisplayName = "Throw a dodgeball"),
	UseAbility UMETA(DisplayName = "Use chosen ability")
};

UCLASS()
class M1DODGEBALL_API ADodgeballCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Our ability system */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystem;

	// For display purposes only
	AActor* HighlightedActor;

	FName TraceTag;

	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(Client, Reliable)
	void InitAbilitySystemClient();

	UAbilitySystemComponent* GetAbilitySystemComponent() const override //We add this function, overriding it from IAbilitySystemInterface.
	{
		return AbilitySystem;
	};

protected:
	/** First person camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	TSubclassOf<class UGameplayAbility> DefaultAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	TSubclassOf<class UGameplayAbility> Ability;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditAnywhere, Category = Camera)
	float BaseLookUpRate;

	//Replicate this
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	int BallCount;
	
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	int Health;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

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

	UFUNCTION(Reliable, Server, WithValidation)
	void PickupBall(FVector ForwardVector);
	void PickupBall_Implementation(FVector ForwardVector);
	bool PickupBall_Validate(FVector ForwardVector);

	void AttemptPickupBall();

public:	
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	// Sets default values for this character's properties
	ADodgeballCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	void Die();

	UFUNCTION(BlueprintPure, Category = Data)
	int GetBallCount() { return BallCount;	};
	void SetBallCount(int NewBallCount) { BallCount = NewBallCount; }

	
	
};
