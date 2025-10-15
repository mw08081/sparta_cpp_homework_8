// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"

#include "Kismet/GameplayStatics.h"

#include "System/BasisDefaultGameMode.h"
#include "Character/CharacterBase.h"
#include "Weapon/WeaponBase.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnDefaultController();

	CurGameMode = Cast<ABasisDefaultGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	CurHP = MaxHP;
}

bool ACharacterBase::GetCanAttack() const
{
	return this->bCanAttack;
}

void ACharacterBase::SetCanAttack(bool _bCanAttack)
{
	this->bCanAttack = _bCanAttack;
}

void ACharacterBase::Attack()
{
	if (bCanAttack == false) return;

	if (Weapon != nullptr)
	{
		Weapon->Fire();
	}
}

void ACharacterBase::Hit(int32 Damage, AActor* ByWho)
{
	//UE_LOG(LogTemp, Display, TEXT("Character Base OnHit"));

	CurHP -= Damage;

	if (CurHP <= 0) {
		static_cast<ACharacterBase*>(ByWho)->IncreaseKillCount();
	}
}


void ACharacterBase::IncreaseKillCount()
{
	//UE_LOG(LogTemp, Display, TEXT("Character Base IncreaseKillCount %d"), KillCount);

	KillCount++;
	CurGameMode->KillEnemy();
}

int32 ACharacterBase::GetAmmoCount() const
{
	return this->AmmoCount;
}

void ACharacterBase::SetAmmoCount(int32 _AmmoCount)
{
	this->AmmoCount = _AmmoCount;
	
	// 보유량 HUD 표시
	CurGameMode->SetPlayerAmmo(AmmoCount);
}

int32 ACharacterBase::GetCurHP() const
{
	return CurHP;
}

void ACharacterBase::SetCurHP(int32 _HP)
{
	this->CurHP = _HP;
	if (CurHP < 0) {
		CurHP = 0;
	}

	CurGameMode->SetPlayerHP((float)CurHP / MaxHP);
}

