// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Training/TrainingTarget.h"

// Sets default values
ATrainingTarget::ATrainingTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ActorRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ActorRoot"));
	RootComponent = ActorRoot;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATrainingTarget::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentHit.AddDynamic(this, &ATrainingTarget::OnHit);
}

// Called every frame
void ATrainingTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsShouldRot) {
		FRotator DeltaRot = RotDirection * RotSpeed * DeltaTime * (IsPositiveSide ? -1 : 1);
		AddActorLocalRotation(DeltaRot);

		CurRotAmmount += RotSpeed * DeltaTime;
		if (CurRotAmmount >= MaxRotAmmount) {
			// 회전중지
			IsShouldRot = false;
			CurRotAmmount = 0;


			if (IsAutoReturn && IsPositiveSide) {
				GetWorld()->GetTimerManager().SetTimer(AutoReturnHandle, this, &ATrainingTarget::ExecRot, FMath::RandRange(1.f, 4.f), false);
			}

			IsPositiveSide = !IsPositiveSide;
		}
	}
}

void ATrainingTarget::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// 동작중이라면 실행하지 않음
	//if (IsShouldTurn == true) return;

	// 자동으로 돌아오는 타겟이 뒤집어져있다면, 실행하지않음
	if (IsAutoReturn && IsPositiveSide == false) return;

	ExecRot();
}

void ATrainingTarget::ExecRot()
{
	IsShouldRot = true;
}

