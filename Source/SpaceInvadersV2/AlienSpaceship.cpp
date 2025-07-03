// Fill out your copyright notice in the Description page of Project Settings.


#include "AlienSpaceship.h"

// Sets default values
AAlienSpaceship::AAlienSpaceship()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");

	Mesh->OnComponentHit.AddDynamic(this, &AAlienSpaceship::Broadcast);
}

// Called when the game starts or when spawned
void AAlienSpaceship::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAlienSpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAlienSpaceship::SetDirection(int value)
{
	Direction = value;
}

uint8 AAlienSpaceship::GetScore()
{
	return Score;
}

void AAlienSpaceship::SetScore(int value)
{
	Score = value;
}

void AAlienSpaceship::Broadcast(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UpdateScoreDelegate.Broadcast(Score);
}