// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpaceshipController.h"

void APlayerSpaceshipController::BeginPlay()
{
	Super::BeginPlay();

    // Retrieve the pawn
    PossessedPawn = Cast<APlayerSpaceship>(GetPawn());
    bAutoManageActiveCameraTarget = false;
}

// Currently when respawning the the player doesn't move despite CallMove
void APlayerSpaceshipController::SetupInputComponent()
{
    Super::SetupInputComponent();

    //Set up gameplay input bindings
    InputComponent->BindAxis("Horizontal", this, &APlayerSpaceshipController::CallMove);
}

void APlayerSpaceshipController::UpdatePossessedPawn(APlayerSpaceship* PawnToPossessed)
{
    if (PawnToPossessed != nullptr)
    {
        PossessedPawn = PawnToPossessed;
    }

}

void APlayerSpaceshipController::CallMove(float AxisValue)
{
    if (PossessedPawn)
    {
        PossessedPawn->Move(AxisValue);
    }
}