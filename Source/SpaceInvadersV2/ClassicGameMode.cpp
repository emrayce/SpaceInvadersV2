// Fill out your copyright notice in the Description page of Project Settings.


#include "ClassicGameMode.h"

void AClassicGameMode::InitGameState()
{
	Super::InitGameState();

	// Fill the matrix and spawn aliens
	SpawnAliens();
}

void AClassicGameMode::SpawnAliens()
{
	TSubclassOf<AActor> AlienToBeSpawned;
	for (uint8 row = 0; row < NB_ALIENS_ROW; row++)
	{
		for (uint8 col = 0; col < NB_ALIENS_COLUMN; col++)
		{
			if (row == 0)
			{
				AlienToBeSpawned = SmallAlien;
			}
			else if (row == 1 || row == 2)
			{
				AlienToBeSpawned = MediumAlien;
			}
			else
			{
				AlienToBeSpawned = BigAlien;
			}

			FVector				  Position(125 * col, 125 * row, 100);
			FRotator			  Rotation(0, 0, 0);
			FTransform			  Transform(Rotation, Position);
			Aliens[row][col] = GetWorld()->SpawnActor<AAlien>(AlienToBeSpawned, Transform);
			Aliens[row][col]->SetYPos(row);
			Aliens[row][col]->SetXPos(col);
		}
	}
}