// Fill out your copyright notice in the Description page of Project Settings.


#include "HomeworkActor.h"

#include "TimerManager.h"

// Sets default values
AHomeworkActor::AHomeworkActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = SM;
}

// Called when the game starts or when spawned
void AHomeworkActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(MovingLogicTimerHandler, this, &AHomeworkActor::Move, MovingInterval, true);
}

void AHomeworkActor::Move()
{
	FVector CurLocation = GetActorLocation();
	SetActorLocation(FVector(CurLocation.X + GetStep(), CurLocation.Y + GetStep(), CurLocation.Z));
	
	if (MovingCnt++ < 10) { 
		UE_LOG(LogTemp, Error, TEXT("Moved(%d) - %s"), MovingCnt, *GetActorLocation().ToCompactString());
	}
	else {
		GetWorldTimerManager().ClearTimer(MovingLogicTimerHandler);
	}
}

int32 AHomeworkActor::GetStep()
{
	return FMath::RandRange(0.f, 2.f);
}

