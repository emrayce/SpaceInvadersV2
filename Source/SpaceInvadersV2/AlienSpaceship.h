// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

#include "AlienSpaceship.generated.h"

UCLASS()
class SPACEINVADERSV2_API AAlienSpaceship : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlienSpaceship();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetDirection(int value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
	float Speed;
	int Direction;
	uint8 Score;

};
