// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Item/ItemSpawner.h"

#include "NavigationSystem.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnItemAtRandomLocaion();
}

// Called every frame
void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemSpawner::SpawnItemAtRandomLocaion()
{
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	if (NavSystem == nullptr) return;

	for (TSubclassOf<AActor> e : SpawnTargets) {
		for (auto i = 0; i < 20; i++) {
			FNavLocation LOC;
			NavSystem->GetRandomPoint(LOC);

			GetWorld()->SpawnActor<AActor>(e.Get(), LOC.Location, FRotator::ZeroRotator);
		}
	}
}

