// Fill out your copyright notice in the Description page of Project Settings.


#include "Alien.h"

// Sets default values
AAlien::AAlien()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AAlien::BeginPlay()
{
	Super::BeginPlay();

	Timer = TimeBeforeMove;
	CurrentLateralMove = 0;
	Direction = 1;
}

// Called every frame
void AAlien::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timer -= DeltaTime;
	if (Timer <= 0)
	{
		if (CurrentLateralMove == LateralMoveNumberBeforeDownMove)
		{
			// Down move
			SetActorLocation(GetActorLocation() + FVector(0, 50, 0));
			Direction = -Direction;
			CurrentLateralMove = 0;
		}
		else
		{
			// Lateral move
			SetActorLocation(GetActorLocation() + FVector(50 * Direction, 0, 0));
			CurrentLateralMove++;
		}
		Timer = TimeBeforeMove;
	}
}

uint8 AAlien::GetColPos() const
{
	return Column;
}

void AAlien::SetColPos(uint8 x)
{
	Column = x;
}

uint8 AAlien::GetRowPos() const
{
	return Row;
}

void AAlien::SetRowPos(uint8 y)
{
	Row = y;
}

AProjectile* AAlien::Shoot()
{
	FVector pos = GetActorLocation() + FVector(0, 50, 0); // give a little offset to spawn in ront of the player
	return GetWorld()->SpawnActor<AProjectile>(ProjectileToSpawn, pos, FRotator(0, 0, 0));
}
