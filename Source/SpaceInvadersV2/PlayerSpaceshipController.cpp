// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpaceshipController.h"

void APlayerSpaceshipController::BeginPlay()
{
	Super::BeginPlay();

    // Retrieve the pawn
    PossessedPawn = Cast<APlayerSpaceship>(GetPawn());
}

void APlayerSpaceshipController::SetupInputComponent()
{
    Super::SetupInputComponent();

    //Set up gameplay input bindings
    InputComponent->BindAxis("Horizontal", this, &APlayerSpaceshipController::CallMove);
    InputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerSpaceshipController::CallShoot);
}

void APlayerSpaceshipController::CallMove(float AxisValue)
{
    GLog->Log("SAUUUUUUTE");
    PossessedPawn->Move(AxisValue);
}

void APlayerSpaceshipController::CallShoot()
{
    GLog->Log("TIIIIIIIIIRE!");
    PossessedPawn->Shoot();
}
