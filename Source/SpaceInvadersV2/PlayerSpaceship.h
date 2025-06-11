// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "Projectile.h"

#include "PlayerSpaceship.generated.h"

UCLASS()
class SPACEINVADERSV2_API APlayerSpaceship : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerSpaceship();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable)
	void Move(float AxisValue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly)
	float Speed;
	UPROPERTY(EditDefaultsOnly)
	UFloatingPawnMovement* MovementComponent; // Needed to move with AddMovementInput
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, NoClear, Category = "Projectile")
	TSubclassOf<AProjectile> Projectile;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	FVector ProjectileOffset;

	// The player can shoot when a condition is fulfilled
	UPROPERTY(BlueprintReadWrite)
	bool CanShoot;

};
