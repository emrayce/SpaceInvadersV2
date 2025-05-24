// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Alien.h"
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
	void SpawnAliens();

private:
	// Matrix holding the references to the aliens
	AAlien* Aliens[NB_ALIENS_ROW][NB_ALIENS_COLUMN];

	UPROPERTY(EditAnywhere, NoClear, Category = "Aliens")
	TSubclassOf<AAlien> SmallAlien;
	UPROPERTY(EditAnywhere, NoClear, Category = "Aliens")
	TSubclassOf<AAlien> MediumAlien;
	UPROPERTY(EditAnywhere, NoClear, Category = "Aliens")
	TSubclassOf<AAlien> BigAlien;
};
