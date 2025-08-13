// Fill out your copyright notice in the Description page of Project Settings.


#include "Alien.h"

// Sets default values
AAlien::AAlien()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	StateMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StateMesh1"));
	StateMesh1->SetupAttachment(RootComponent);
	StateMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StateMesh2"));
	StateMesh2->SetupAttachment(RootComponent);

	//Subscribe the trigger alien death when a mesh is hit
	StateMesh1->OnComponentHit.AddDynamic(this, &AAlien::TriggerAlienDeath);
	StateMesh2->OnComponentHit.AddDynamic(this, &AAlien::TriggerAlienDeath);

	// Set the second mesh to invisible and disable physics to avoid projectile hitting unseen mesh.
	StateMesh2->SetVisibility(false);
	StateMesh2->SetGenerateOverlapEvents(false);
}

// Called when the game starts or when spawned
void AAlien::BeginPlay()
{
	Super::BeginPlay();

	Timer = TimeBeforeMove;
	CurrentLateralMove = 0;
	Direction = 1;

	StateMesh1->SetRelativeLocation(FVector(0, 0, 0));
	StateMesh2->SetRelativeLocation(FVector(0, 0, 0));
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
			// Trigger animation
			SwitchAnimationState();
			// Each time an alien go down he moves a little bit faster by 10%
			TimeBeforeMove -= TimeBeforeMove * 0.1f;
		}
		else
		{
			// Lateral move
			SetActorLocation(GetActorLocation() + FVector(50 * Direction, 0, 0));
			CurrentLateralMove++;
			// Trigger animation
			SwitchAnimationState();
		}
		Timer = TimeBeforeMove;
	}
}

uint8 AAlien::GetColPos() const
{
	return Col;
}

void AAlien::SetColPos(uint8 x)
{
	Col = x;
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

void AAlien::TriggerAlienDeath(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AlienDeathDelegate.Broadcast(Col, Row, Score);
	Destroy();
}

// Fake an animation by changing the visible mesh. Called when alien moves.
void AAlien::SwitchAnimationState()
{
	// if state 1 pass to state 2
	if (StateMesh1->IsVisible())
	{
		StateMesh1->SetVisibility(false);
		StateMesh1->SetGenerateOverlapEvents(false);

		StateMesh2->SetVisibility(true);
		StateMesh2->SetGenerateOverlapEvents(true);	
	}
	// else pass to state 2
	else
	{
		StateMesh2->SetVisibility(false);
		StateMesh2->SetGenerateOverlapEvents(false);

		StateMesh1->SetVisibility(true);
		StateMesh1->SetGenerateOverlapEvents(true);
	}
}
