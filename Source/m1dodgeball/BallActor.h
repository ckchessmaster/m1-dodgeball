// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallActor.generated.h"

UCLASS()
class M1DODGEBALL_API ABallActor : public AActor
{
	GENERATED_BODY()
	
	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	bool bShouldDieOnHit;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
	class UStaticMeshComponent* BallMesh;

	/** Sphere collision component */
	UPROPERTY(VisibleAnywhere, Category = Projectile)
	class USphereComponent* CollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, ReplicatedUsing = OnHitBP)
	bool IsActive;

public:	
	ABallActor(const FObjectInitializer& ObjectInitializer);

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic)
	void OnHitBP();

	void SetIsActive(bool Active) { IsActive = Active; };

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
	
	UStaticMeshComponent* GetMeshComponent() { return BallMesh; }
	void SetDieOnHit(bool Val) { bShouldDieOnHit = Val; }
};
