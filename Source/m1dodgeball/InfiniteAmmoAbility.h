// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DodgeballGameplayAbility.h"
#include "InfiniteAmmoAbility.generated.h"

/**
 * 
 */
UCLASS()
class M1DODGEBALL_API UInfiniteAmmoAbility : public UDodgeballGameplayAbility
{
	GENERATED_BODY()
	
public:
	UInfiniteAmmoAbility(const FObjectInitializer& ObjectInitializer);

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	
	
};
