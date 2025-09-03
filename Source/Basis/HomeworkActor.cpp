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
	
	InitLocation = GetActorLocation();
	GetWorldTimerManager().SetTimer(MovingLogicTimerHandler, this, &AHomeworkActor::Move, MovingInterval, true);
}

void AHomeworkActor::Move()
{
	// 현재위치를 기반으로 새로운 위치를 설정
	FVector CurLocation = GetActorLocation();
	SetActorLocation(FVector(CurLocation.X + GetStep(), CurLocation.Y + GetStep(), CurLocation.Z));
	
	// 이벤트 발생 여부 판단
	if (FMath::RandRange(0.f, 1.f) > 0.5)
	{
		EventFunc();
	}

	// 무빙카운트에 따른 작업분기
	if (MovingCnt++ < 10) { 
		UE_LOG(LogTemp, Error, TEXT("Moved(%d) - CurLocation: %s, Moved Distande: %f"), MovingCnt, *GetActorLocation().ToCompactString(), FVector::Dist(GetActorLocation(), CurLocation));
	}
	else {
		GetWorldTimerManager().ClearTimer(MovingLogicTimerHandler);
		UE_LOG(LogTemp, Warning, TEXT("Moving Finished - Total Moving Distance: %f, Total Event Count: %d"), FVector::Dist(GetActorLocation(), InitLocation), EventCnt);
	}
}

int32 AHomeworkActor::GetStep()
{
	return FMath::RandRange(0.f, 2.f);
}

void AHomeworkActor::EventFunc()
{
	UE_LOG(LogTemp, Warning, TEXT("Event occurred!!!"));
	EventCnt++;
}

