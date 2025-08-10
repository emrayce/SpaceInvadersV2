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
	AlienSpaceshipSpawnTimer = FMath::RandRange(5.0f, 15.0f);
	AlienRespawnTimer = 2.0f;
	AlienSpaceshipDirection = -1; // First spaceship spawns to the right and goes the left
	Defeat = false;

	DeathMenuWidget = CreateWidget(GetWorld(), DeathMenuWidgetReference);

	SpawnAliens();

}

void AClassicGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentAttackDelay -= DeltaTime;
	AlienSpaceshipSpawnTimer -= DeltaTime;

	// Player's death
	if (PlayerLife == 0)
	{
		Defeat = true;
	}
	// Display the death menu
	if (Defeat && !DeathMenuWidget->GetIsVisible())
	{
		GetWorld()->GetFirstPlayerController()->SetPause(true);
		DeathMenuWidget->AddToViewport();
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	}
	// When all aliens are dead, trigger the respawn after a few seconds
	if (AlienCount == 0)
	{
		AlienRespawnTimer -= DeltaTime;
		if (AlienRespawnTimer <= 0)
		{
			SpawnAliens();
			AlienRespawnTimer = 2.0f;
		}
	}
	// Make an alen shoot
	if (AlienCount > 0 && CurrentAttackDelay <= 0)
	{
		MakeAlienShoot();
		CurrentAttackDelay = FMath::RandRange(0.5f, 4.0f);
	}

	// Spawn an alien spaceship
	if (AlienCount > 0 && AlienSpaceshipSpawnTimer <= 0)
	{
		SpawnAlienSpaceship();
		AlienSpaceshipSpawnTimer = FMath::RandRange(5.0f, 15.0f);
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

			// Spawn and init the alien
			FActorSpawnParameters ActorSpawnParameters;
			ActorSpawnParameters.CustomPreSpawnInitalization = [&](AActor* tmpAlien)
				{
					Cast<AAlien>(tmpAlien)->SetColPos(col);
					Cast<AAlien>(tmpAlien)->SetRowPos(row);
				};
			FVector				  Position(125 * col, 125 * row, 100);
			FTransform			  Transform(FRotator(0, 0, 0), Position);
			Aliens[Index(row, col)] = GetWorld()->SpawnActor<AAlien>(AlienToBeSpawned, Transform, ActorSpawnParameters);
			// Bind to the delegate trigerring on Alien death
			Aliens[Index(row, col)]->AlienDeathDelegate.AddUObject(this, &AClassicGameMode::AlienDeath);
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
			// Score is randomly 50 or 100
			int score = FMath::RandRange(1, 2) % 2 == 0 ? 50 : 100;
			Cast<AAlienSpaceship>(tmpSpaceship)->SetScore(score);
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
	spaceship->UpdateScoreDelegate.AddUObject(this, &AClassicGameMode::IncreaseScore);

	// Change direcion of the next spaceship
	AlienSpaceshipDirection = -AlienSpaceshipDirection;
}

void AClassicGameMode::IncreaseScore(uint8 value)
{
	Score += value;
	UpdateUIScoreDelegate.Broadcast(Score);
}

void AClassicGameMode::AlienDeath(uint8 col, uint8 row, uint8 score)
{
	IncreaseScore(score);
	RemoveAlien(col, row);
}

void AClassicGameMode::SetDefeat(bool IsDefeat)
{
	Defeat = IsDefeat;
}

// Replace a pointer to an AAlien by a nullptr. Keeping the size of the array.
void AClassicGameMode::RemoveAlien(uint8 col, uint8 row)
{
	Aliens[Index(row, col)] = nullptr;
	AlienCount--;
}

void AClassicGameMode::MakeAlienShoot()
{
	int32 randIndex = 0;

	do
	{
		randIndex = FMath::RandRange(0, Aliens.Num() - 1);
	} while (AlienCount > 0 && Aliens[randIndex] == nullptr);
	// This prevent an infinite loop when all aliens are dead and it searches eternally for a valid shooter
	if (Aliens[randIndex] != nullptr)
	{
		Aliens[randIndex]->Shoot();
	}
}
