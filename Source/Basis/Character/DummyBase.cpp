// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DummyBase.h"

#include "Components/SkeletalMeshComponent.h"

#include "Character/CharacterBase.h"

void ADummyBase::BeginPlay()
{
	Super::BeginPlay();

	OrgLocation = GetActorLocation();
	TargetLocation = OrgLocation + MovingDirection.GetSafeNormal() * MovingDistance;

	OrgRot = GetMesh()->GetRelativeRotation();
	TargetRot = OrgRot + -1 * RotDirection * 90;
}

void ADummyBase::Tick(float DeltaTime)
{
	Moving(DeltaTime);
	Rotating(DeltaTime);
}

void ADummyBase::Moving(float DeltaTime)
{
	if (IsPositiveSide == false) return;

	FVector DeltaLocation = MovingDirection.GetSafeNormal() * MovingSpeed * DeltaTime * (IsMoveToTarget ? 1 : -1);
	CurMovingDist += MovingSpeed * DeltaTime;

	if (CurMovingDist >= MovingDistance) {
		IsMoveToTarget = !IsMoveToTarget;
		CurMovingDist = 0;
	}

	SetActorLocation(GetActorLocation() + DeltaLocation);
}


void ADummyBase::Rotating(float DeltaTime)
{
	if (IsShouldRot) {
		FRotator DeltaRot = RotDirection * RotSpeed * DeltaTime * (IsPositiveSide ? -1 : 1);
		GetMesh()->AddLocalRotation(DeltaRot);

		CurRotAmmount += RotSpeed * DeltaTime;
		if (CurRotAmmount >= 90) {
			// 회전중지
			IsShouldRot = false;
			CurRotAmmount = 0;

			if (IsPositiveSide == true) {
				GetMesh()->SetRelativeRotation(TargetRot);
				GetWorld()->GetTimerManager().SetTimer(AutoReturnHandle, this, &ADummyBase::ExecRot, FMath::RandRange(1.f, 4.f), false);
			}
			else {
				GetMesh()->SetRelativeRotation(OrgRot);
			}

			IsPositiveSide = !IsPositiveSide;
		}
	}
}

void ADummyBase::ExecRot()
{
	IsShouldRot = true;
	CurHP = MaxHP;
}

void ADummyBase::Hit(int32 Damage, AActor* ByWho)
{
	Super::Hit(Damage, ByWho);

	if (CurHP < 0) {
		ExecRot();
	}
}
