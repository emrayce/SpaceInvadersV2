// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Blueprint/UserWidget.h"
#include "PlayerSpaceship.h"

#include "PlayerSpaceshipController.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetPauseSignature, bool, IsPause);

UCLASS()
class SPACEINVADERSV2_API APlayerSpaceshipController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	UFUNCTION(BlueprintCallable)
	void UpdatePossessedPawn(APlayerSpaceship* PawnToPossessed);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FSetPauseSignature SetPauseTrigger;

protected:
	
	void CallMove(float AxisValue);
	void Pause();
	UPROPERTY(BlueprintReadWrite)
	APlayerSpaceship* PossessedPawn;
	// widget reference so that we can create a widget on startup
	UPROPERTY(EditDefaultsOnly, NoClear, Category = "UI")
	TSubclassOf<UUserWidget> WidgetReference;
	// actual reference to the created widget
	UPROPERTY()
	UUserWidget* CreatedWidget;
};
