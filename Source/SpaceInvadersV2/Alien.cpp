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
	Direction = -1;

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
			SetActorLocation(GetActorLocation() + FVector(0, 100, 0));
			Direction = -Direction;
			CurrentLateralMove = 0;
		}
		else
		{
			// Lateral move
			SetActorLocation(GetActorLocation() + FVector(100 * Direction, 0, 0));
			CurrentLateralMove++;
		}
		Timer = TimeBeforeMove;
	}
}

uint8 AAlien::GetXPos()
{
	return XPos;
}

void AAlien::SetXPos(uint8 x)
{
	XPos = x;
}

uint8 AAlien::GetYPos()
{
	return YPos;
}

void AAlien::SetYPos(uint8 y)
{
	YPos = y;
}