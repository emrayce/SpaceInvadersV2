// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

#include "Projectile.h"

#include "Alien.generated.h"


DECLARE_MULTICAST_DELEGATE_ThreeParams(FAlienDeathSignature, uint8 /*col*/, uint8 /*row*/, uint8 /*score*/);


UCLASS()
class SPACEINVADERSV2_API AAlien : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlien();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	uint8 GetColPos() const;
	void  SetColPos(uint8 x);
	uint8 GetRowPos() const;
	void  SetRowPos(uint8 y);

	AProjectile* Shoot();
	FAlienDeathSignature AlienDeathDelegate; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void TriggerAlienDeath(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void SwitchAnimationState();

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneComponent;
	// Since the animation is only 1 frame and we have only 3 assets without any transitions
	// It's simpler to just activate and deactivate a state mesh anytime an alien move
	// Also unreal animation handling is very complex and i want to finish this and move on to another project.
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StateMesh1;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StateMesh2;
		;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile> ProjectileToSpawn;

	// Position of the alien in the alien list
	UPROPERTY(BlueprintReadOnly)
	uint8 Col;
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 Score;

};
