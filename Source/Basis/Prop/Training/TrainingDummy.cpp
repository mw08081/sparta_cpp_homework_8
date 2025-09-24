// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Training/TrainingDummy.h"

// Sets default values
ATrainingDummy::ATrainingDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATrainingDummy::BeginPlay()
{
	Super::BeginPlay();

	OrgLocation = GetActorLocation();
	TargetLocation = OrgLocation + MovingDirection.GetSafeNormal() * MovingDistance;

	DrawDebugSphere(GetWorld(), OrgLocation, 10, 24, FColor::Red, true);
	DrawDebugSphere(GetWorld(), TargetLocation, 10, 24, FColor::Blue, true);
}

// Called every frame
void ATrainingDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector DeltaLocation = MovingDirection.GetSafeNormal() * MovingSpeed * DeltaTime * (IsMoveToTarget ? 1 : -1);
	CurMovingDist += MovingSpeed * DeltaTime;

	if (CurMovingDist >= MovingDistance) {
		IsMoveToTarget = !IsMoveToTarget;
		CurMovingDist = 0;
	}

	SetActorLocation(GetActorLocation() + DeltaLocation);
}

