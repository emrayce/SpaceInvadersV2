// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpaceship.h"

// Sets default values
APlayerSpaceship::APlayerSpaceship()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");

}

// Called when the game starts or when spawned
void APlayerSpaceship::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerSpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerSpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//InputComponent->BindAxis("Horizontal", this, &APlayerSpaceship::Move);
	//InputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerSpaceship::Shoot);

}

void APlayerSpaceship::Shoot()
{
	// do nothing yet
}

void APlayerSpaceship::Move(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

