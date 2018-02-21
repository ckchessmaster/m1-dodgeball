// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "DodgeballGameplayAbility.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Info)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Info)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Info)
	UTexture2D* Image;
};

UCLASS()
class M1DODGEBALL_API UDodgeballGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Info)
	FAbilityInfo AbilityInfo;

public:
	UFUNCTION(BlueprintPure)
	FAbilityInfo GetAbilityInfo() { return AbilityInfo; }
};
