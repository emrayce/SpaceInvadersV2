// Fill out your copyright notice in the Description page of Project Settings.


#include "ClassicGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

void AClassicGameMode::InitGameState()
{
	Super::InitGameState();
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Init and fill the matrix and spawn aliens
	AlienCount = 0;
	Score = 0; 
	CurrentAttackDelay = FMath::RandRange(0.5f, 4.0f);
	SpawnAliens();
	SpawnTimer = FMath::RandRange(5.0f, 15.0f);
	AlienSpaceshipDirection = -1; // First spaceship spawns to the right and goes the left
}

void AClassicGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentAttackDelay -= DeltaTime;
	if (PlayerLife == 0 || AlienCount == 0)
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->ConsoleCommand("quit");
	}
	if (CurrentAttackDelay <= 0)
	{
		MakeAlienShoot();
		CurrentAttackDelay = FMath::RandRange(0.5f, 4.0f);
	}

	SpawnTimer -= DeltaTime;
	if (SpawnTimer <= 0)
	{
		SpawnAlienSpaceship();
		SpawnTimer = FMath::RandRange(5.0f, 15.0f);
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
			FTransform			  Transform(FRotator(0, 0, 0), Position);
			Aliens[Index(row, col)] = GetWorld()->SpawnActor<AAlien>(AlienToBeSpawned, Transform);
			Aliens[Index(row, col)]->SetRowPos(row);
			Aliens[Index(row, col)]->SetColPos(col);
			++AlienCount;
		}
	}
}

void AClassicGameMode::SpawnAlienSpaceship()
{
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.CustomPreSpawnInitalization = [&](AActor* tmpSpaceship)
		{
			Cast<AAlienSpaceship>(tmpSpaceship)->SetDirection(AlienSpaceshipDirection);
		};
	FTransform transform;
	if (AlienSpaceshipDirection == -1)
	{
		transform = FTransform(FRotator(0, 0, 0), FVector(2000, -100, 50));

	}
	else if (AlienSpaceshipDirection == 1)
	{
		transform = FTransform(FRotator(0, 0, 0), FVector(-200, -100, 50));
	}
	AAlienSpaceship* spaceship = GetWorld()->SpawnActor<AAlienSpaceship>(AlienSpaceship, transform, ActorSpawnParameters);
	spaceship->SetDirection(AlienSpaceshipDirection);

	// Change direcion of the next spaceship
	AlienSpaceshipDirection = -AlienSpaceshipDirection;
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
