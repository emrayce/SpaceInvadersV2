// Fill out your copyright notice in the Description page of Project Settings.


#include "DefeatTrigger.h"
#include "ClassicGameMode.h"

// Sets default values
ADefeatTrigger::ADefeatTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxTrigger = CreateDefaultSubobject<UBoxComponent>("BoxTrigger");
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADefeatTrigger::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ADefeatTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefeatTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADefeatTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Trigger defeat when alien overlaps the box
	AAlien* AlienOverlapping = Cast<AAlien>(OtherActor);
	if (AlienOverlapping)
	{
		AClassicGameMode* GameMode = Cast<AClassicGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->SetDefeat(true);
		}
	}
}

