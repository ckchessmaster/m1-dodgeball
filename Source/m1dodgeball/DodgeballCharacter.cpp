// Fill out your copyright notice in the Description page of Project Settings.

#include "DodgeballCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystemComponent.h"
#include "Engine.h"
#include "BallActor.h"
#include "Net/UnrealNetwork.h"


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

	bReplicates = true;
	bReplicateMovement = true;

	bCanBeDamaged = true;

}

void ADodgeballCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(ADodgeballCharacter, BallCount);
	DOREPLIFETIME(ADodgeballCharacter, Health);
}//end GetLifetimeReplicatedProps

// Called to bind functionality to input
void ADodgeballCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ADodgeballCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADodgeballCharacter::MoveRight);

	// "turn" handles devices that provide an absolute delta, such as a mouse.
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// Used to pickup a dodgeball
	PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &ADodgeballCharacter::AttemptPickupBall);

	// Bind input to the ability system
	AbilitySystem->BindAbilityActivationToInputComponent(PlayerInputComponent, FGameplayAbiliyInputBinds("ConfirmInput", "CancelInput", "AbilityType"));
}

void ADodgeballCharacter::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystem) {
		if (HasAuthority() && DefaultAttack) {
			AbilitySystem->GiveAbility(FGameplayAbilitySpec(DefaultAttack.GetDefaultObject(), 1, 0));
		}

		AbilitySystem->InitAbilityActorInfo(this, this);
		InitAbilitySystemClient();
	}

	SetOwner(NewController);
}

void ADodgeballCharacter::InitAbilitySystemClient_Implementation()
{
	if (AbilitySystem)
	{
		AbilitySystem->InitAbilityActorInfo(this, this);
	}
}

// Called when the game starts or when spawned
void ADodgeballCharacter::BeginPlay()
{
	Super::BeginPlay();

	 // Start the game with a ball
	BallCount = 1;
	Health = 1;

	TraceTag = FName("TestTag");

	GetWorld()->DebugDrawTraceTag = TraceTag;
}

// Called every frame
void ADodgeballCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Highlight the ball if we are looking at it

	FCollisionQueryParams CollisionParams;
	//CollisionParams.TraceTag = TraceTag; // Used to draw debug lines ingame

	//Re-initialize hit info
	FHitResult Hit(ForceInit);

	UCameraComponent* Camera = GetFirstPersonCameraComponent();
	FVector FinalLocation = (Camera->GetForwardVector() * 5000) + Camera->GetComponentLocation();
	GetWorld()->LineTraceSingleByChannel(Hit, Camera->GetComponentLocation(), FinalLocation, ECollisionChannel::ECC_Visibility, CollisionParams);

	ABallActor* ball = Cast<ABallActor>(Hit.Actor.Get());

	if (ball) {
		Cast<ABallActor>(Hit.Actor.Get())->GetMeshComponent()->SetRenderCustomDepth(true);
		HighlightedActor = ball;
	} else {
		// Unhighlight the actor
		if (HighlightedActor) {
			ABallActor* ball = Cast<ABallActor>(HighlightedActor);
			ball->GetMeshComponent()->SetRenderCustomDepth(false);
			HighlightedActor = nullptr;
		}// end if
	}//end if/else
}
float ADodgeballCharacter::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	
	if (HasAuthority()) {
		Health -= FinalDamage;

		if (Health <= 0) {
			Die();
		}
	}
	return FinalDamage;
}
// end tick

void ADodgeballCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}//end moveforward

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

void ADodgeballCharacter::AttemptPickupBall()
{
	PickupBall(GetFirstPersonCameraComponent()->GetForwardVector());
}

bool ADodgeballCharacter::PickupBall_Validate(FVector ForwardVector)
{
	return true;
}

void ADodgeballCharacter::PickupBall_Implementation(FVector ForwardVector)
{
	if (HasAuthority()) {
		FCollisionQueryParams CollisionParams;
		CollisionParams.TraceTag = TraceTag;
		FHitResult Hit(ForceInit);
		UCameraComponent* Camera = GetFirstPersonCameraComponent();
		FVector FinalLocation = (ForwardVector * 5000) + Camera->GetComponentLocation();
		GetWorld()->LineTraceSingleByChannel(Hit, Camera->GetComponentLocation(), FinalLocation, ECollisionChannel::ECC_Visibility, CollisionParams);

		ABallActor* ball = Cast<ABallActor>(Hit.Actor.Get());

		if (ball) {
			BallCount++;
			ball->Destroy();
		}
	}
}

void ADodgeballCharacter::Die_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "I'M DEAD!!!!");
	
	if (HasAuthority()) {
		AActor* Owner = GetOwner();
		APlayerController* Player = Cast<APlayerController>(Owner);

		if (Player) {
			// Get the spectator spawn location
			FVector SpawnLocation;
			for (TActorIterator<APlayerStart> Itr(GetWorld()); Itr; ++Itr) {
				if (Itr->PlayerStartTag.Compare("0") == 0) {
					SpawnLocation = Itr->GetActorLocation();
				}
			}

			ASpectatorPawn* NewSpectator = GetWorld()->SpawnActor<ASpectatorPawn>(SpawnLocation, FRotator());
			if (NewSpectator) {
				Player->Possess(NewSpectator);
			}
		}
	}

	Tags.Add("Dead");

	// For animation
	DieBP();

	Destroy();
}
