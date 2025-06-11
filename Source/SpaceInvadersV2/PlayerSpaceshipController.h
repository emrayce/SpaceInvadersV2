// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "PlayerSpaceship.h"

#include "PlayerSpaceshipController.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADERSV2_API APlayerSpaceshipController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	UFUNCTION(BlueprintCallable)
	void UpdatePossessedPawn(APlayerSpaceship* PawnToPossessed);

protected:
	
	void CallMove(float AxisValue);
	UPROPERTY(BlueprintReadWrite)
	APlayerSpaceship* PossessedPawn;
};
