// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "AlienSpaceship.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateScoreSignature, uint8 /*Score*/);

UCLASS()
class SPACEINVADERSV2_API AAlienSpaceship : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlienSpaceship();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void  SetDirection(int value);
	uint8 GetScore();
	void  SetScore(int value);

	FUpdateScoreSignature UpdateScoreDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void BroadcastScore(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UProjectileMovementComponent* MovementComponent;
	float Speed;
	UPROPERTY(BlueprintReadOnly)
	int Direction; // 1 is right -1 is left
	uint8 Score;
};
