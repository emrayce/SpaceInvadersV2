// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Alien.h"
#include "AlienSpaceship.h"
#include "GameCamera.h"

#include "ClassicGameMode.generated.h"

/**
 * 
 */

#define NB_ALIENS_ROW	 5
#define NB_ALIENS_COLUMN 11

UCLASS()
class SPACEINVADERSV2_API AClassicGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void InitGameState() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable)
	void RemoveAlien(uint8 col, uint8 row);
	UFUNCTION(BlueprintCallable)
	void MakeAlienShoot();
	uint8 Index(uint8 row, uint8 column);

private:
	void SpawnAliens();
	void SpawnAlienSpaceship();

protected:
	// Matrix holding the references to the aliens
	UPROPERTY(BlueprintReadOnly)
	TArray<AAlien*> Aliens;
	UPROPERTY(EditDefaultsOnly, NoClear, Category = "Aliens")
	TSubclassOf<AAlien> SmallAlien;
	UPROPERTY(EditDefaultsOnly, NoClear, Category = "Aliens")
	TSubclassOf<AAlien> MediumAlien;
	UPROPERTY(EditDefaultsOnly, NoClear, Category = "Aliens")
	TSubclassOf<AAlien> BigAlien;
	UPROPERTY(EditDefaultsOnly, NoClear, Category = "Aliens")
	TSubclassOf<AAlienSpaceship> AlienSpaceship;

	// Score of player
	UPROPERTY(BlueprintReadWrite)
	int32 Score;
	// Number of alien. Once it reaches 0 it's the end
	UPROPERTY(BlueprintReadWrite)
	int32 AlienCount;
	// Player's life. once it reaches 0 it 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	uint8 PlayerLife;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	AGameCamera* Camera;

private:
	// Current time between two shots
	float CurrentAttackDelay;
	float SpawnTimer;
	int	  AlienSpaceshipDirection; // 1 is right -1 is left
};
