// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

#include "Projectile.h"

#include "Alien.generated.h"


UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateAlien, uint8, col, uint8, row);

UCLASS()
class SPACEINVADERSV2_API AAlien : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlien();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	uint8 GetColPos();
	void  SetColPos(uint8 x);
	uint8 GetRowPos();
	void  SetRowPos(uint8 y);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Collider;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile> ProjectileToSpawn;

	// Position of the alien in the alien list
	UPROPERTY(BlueprintReadOnly)
	uint8 Column;
	UPROPERTY(BlueprintReadOnly)
	uint8 Row;
	// Waiting time before another movement
	UPROPERTY(EditDefaultsOnly, Category = "AlienMovement")
	float TimeBeforeMove; // TODO: Has to be changed as the number of aliens go down
	float Timer;
	// Number of lateral move before a down move
	UPROPERTY(EditDefaultsOnly, Category = "AlienMovement")
	uint8 LateralMoveNumberBeforeDownMove;
	uint8 CurrentLateralMove;
	// Decide if it goes to the left or the right
	int Direction;

	UPROPERTY(EditAnywhere, Category = "AlienMovement")
	int Speed;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FUpdateAlien UpdateAlienTrigger;
};
