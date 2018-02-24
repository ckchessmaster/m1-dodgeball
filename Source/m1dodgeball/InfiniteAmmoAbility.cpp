// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteAmmoAbility.h"
#include "DodgeballCharacter.h"
#include "GameplayTagsModule.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEffectRemoved.h"


UInfiniteAmmoAbility::UInfiniteAmmoAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UInfiniteAmmoAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//ADodgeballCharacter* Player = Cast<ADodgeballCharacter>(ActorInfo->OwnerActor.Get());

	//FActiveGameplayEffectHandle durationHandle = Player->GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(AbilityDurationEffect.GetDefaultObject(), 1.f, FGameplayEffectContextHandle());
	//
	//// Store old details
	//int oldBallCount = Player->GetBallCount();
	//Player->SetBallCount(999);

	//UAbilityTask_WaitGameplayEffectRemoved* test = UAbilityTask_WaitGameplayEffectRemoved::WaitForGameplayEffectRemoved(this, durationHandle);
	//
	//Player->SetBallCount(oldBallCount);

	//CommitAbility(Handle, ActorInfo, ActivationInfo);
	//EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}


