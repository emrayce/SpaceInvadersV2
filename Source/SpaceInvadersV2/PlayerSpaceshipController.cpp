// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpaceshipController.h"

void APlayerSpaceshipController::BeginPlay()
{
	Super::BeginPlay();

    // Retrieve the pawn
    PossessedPawn = Cast<APlayerSpaceship>(GetPawn());
    bAutoManageActiveCameraTarget = false;

    CreatedWidget = CreateWidget(GetWorld(), WidgetReference);
}

// Currently when respawning the the player doesn't move despite CallMove
void APlayerSpaceshipController::SetupInputComponent()
{
    Super::SetupInputComponent();

    //Set up gameplay input bindings
    InputComponent->BindAxis("Horizontal", this, &APlayerSpaceshipController::CallMove);
    InputComponent->BindAction("Pause", IE_Pressed, this, &APlayerSpaceshipController::Pause).bExecuteWhenPaused = true;
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

void APlayerSpaceshipController::Pause()
{
    SetPause(!IsPaused());
    if (IsPaused())
    {
        CreatedWidget->AddToViewport();
        bShowMouseCursor = true;
    }
    else
    {
        CreatedWidget->RemoveFromParent();
        bShowMouseCursor = false;
    }
}