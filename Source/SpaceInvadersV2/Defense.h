// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Defense.generated.h"

UCLASS()
class SPACEINVADERSV2_API ADefense : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefense();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly)
	TArray<UStaticMeshComponent*> Meshes;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
