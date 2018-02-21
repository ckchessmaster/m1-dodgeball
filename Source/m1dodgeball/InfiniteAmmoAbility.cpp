// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteAmmoAbility.h"
#include "DodgeballCharacter.h"

UInfiniteAmmoAbility::UInfiniteAmmoAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UInfiniteAmmoAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ADodgeballCharacter* Player = Cast<ADodgeballCharacter>(ActorInfo->OwnerActor.Get());
	Player->SetBallCount(99);

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}


