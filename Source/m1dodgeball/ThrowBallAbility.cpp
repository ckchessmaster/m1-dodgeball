// Fill out your copyright notice in the Description page of Project Settings.

#include "ThrowBallAbility.h"
#include "Engine.h"
#include "DodgeballCharacter.h"


bool UThrowBallAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayTagContainer * SourceTags, const FGameplayTagContainer * TargetTags, OUT FGameplayTagContainer * OptionalRelevantTags) const
{
	bool CanActivate = Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
	return CanActivate;
}

void UThrowBallAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (BallClass != nullptr && ActorInfo->PlayerController != nullptr) {
		ADodgeballCharacter* Owner = Cast<ADodgeballCharacter>(ActorInfo->OwnerActor.Get());
		UWorld* const World = GetWorld();
		if (World /*&& Owner->GetBallCount() > 0*/) {
			const FRotator SpawnRotation = ActorInfo->PlayerController->GetControlRotation();
			const FVector SpawnLocation = Owner->GetActorLocation() + (Owner->GetActorForwardVector() * 2);

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			ABallActor* Ball = World->SpawnActor<ABallActor>(BallClass, SpawnLocation, SpawnRotation, SpawnParams);
			Ball->SetIsActive(true);
			Ball->SetOwner(ActorInfo->PlayerController.Get());

			// Decrement ball count
			Owner->SetBallCount(Owner->GetBallCount() - 1);
		}//end world check
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
