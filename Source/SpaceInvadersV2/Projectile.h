// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Projectile.generated.h"


UCLASS()
class SPACEINVADERSV2_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* MovementComponent;
	UPROPERTY(EditDefaultsOnly)
	//USphereComponent* Collider;
	//UPROPERTY(EditAnywhere)
	float Speed;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
