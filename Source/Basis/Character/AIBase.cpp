// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AIBase.h"

#include "Weapon/WeaponBase.h"
#include "Character/PlayerBase.h"

void AAIBase::BeginPlay()
{
	Super::BeginPlay();

	Weapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass);
	if (Weapon != nullptr)
	{
		FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
		Weapon->AttachToComponent(GetMesh(), TransformRules, TEXT("WeaponSocket"));
		Weapon->SetOwner(this);

		Weapon->SetActorRelativeLocation(FVector(-0.223613, -6.477133, -2.791346));
	}
}

void AAIBase::Attack()
{
	Super::Attack(); 
}

void AAIBase::Hit(int32 Damage, AActor* ByWho)
{
	Super::Hit(Damage, ByWho);

	if (CurHP < 0) {

		if (IsValid(Weapon))
		{
			Weapon->Destroy();
		}
		Destroy();
	}
}

void AAIBase::IncreaseKillCount()
{
}
