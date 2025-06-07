// Fill out your copyright notice in the Description page of Project Settings.


#include "ClassicGameMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Math/UnrealMathUtility.h"

void AClassicGameMode::InitGameState()
{
	Super::InitGameState();

	// Init and fill the matrix and spawn aliens
	AlienCount = 0;
	Score = 0;
	CurrentAttackDelay = AttackDelay;
	SpawnAliens();

}

void AClassicGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentAttackDelay -= DeltaTime;
	if (CurrentAttackDelay <= 0)
	{
		MakeAlienShoot();
		CurrentAttackDelay = AttackDelay;
	}
}

uint8 AClassicGameMode::Index(uint8 row, uint8 column)
{
	return row + (column * NB_ALIENS_ROW);
} 

void AClassicGameMode::SpawnAliens()
{
	Aliens.Init(nullptr, NB_ALIENS_COLUMN * NB_ALIENS_ROW);
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
			Aliens[Index(row, col)] = GetWorld()->SpawnActor<AAlien>(AlienToBeSpawned, Transform);
			Aliens[Index(row, col)]->SetRowPos(row);
			Aliens[Index(row, col)]->SetColPos(col);
			++AlienCount;
		}
	}
}

// Replace a pointer to an AAlien by a nullptr. Keeping the size of the array.
void AClassicGameMode::RemoveAlien(uint8 row, uint8 col)
{
	Aliens[Index(row, col)] = nullptr;
}

void AClassicGameMode::MakeAlienShoot()
{
	int32 randIndex = 0;

	do
	{
		randIndex = FMath::RandRange(0, Aliens.Num() - 1);
	} while (Aliens[randIndex] == nullptr);

	Aliens[randIndex]->Shoot();


}
