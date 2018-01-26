// Fill out your copyright notice in the Description page of Project Settings.

#include "DodgeballCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystemComponent.h"
#include "Engine.h"
#include "BallActor.h"


// Sets default values
ADodgeballCharacter::ADodgeballCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Our ability system component.
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
}

// Called to bind functionality to input
void ADodgeballCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	//PlayerInputComponent->BindAction("Throw", IE_Pressed, this, &ADodgeballCharacter::ThrowBall);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ADodgeballCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADodgeballCharacter::MoveRight);

	// "turn" handles devices that provide an absolute delta, such as a mouse.
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// Used to pickup a dodgeball
	//PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &ADodgeballCharacter::PickupBall);

	// Bind input to the ability system
	AbilitySystem->BindAbilityActivationToInputComponent(PlayerInputComponent, FGameplayAbiliyInputBinds("ConfirmInput", "CancelInput", "AbilityType"));
}

// Called when the game starts or when spawned
void ADodgeballCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add more abilities like this:
	if (AbilitySystem) {
		if (HasAuthority() && DefaultAttack) {
			AbilitySystem->GiveAbility(FGameplayAbilitySpec(DefaultAttack.GetDefaultObject(), 1, 0));
		}
		AbilitySystem->InitAbilityActorInfo(this, this);
	}//end ability system init

	// Start the game with a ball
	BallCount = 1;
	Health = 1;
}

// Called every frame
void ADodgeballCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADodgeballCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ADodgeballCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ADodgeballCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADodgeballCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADodgeballCharacter::Die()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "I'M DEAD!!!!");
}
