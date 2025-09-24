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

	//UE_LOG(LogTemp, Display, TEXT("Character Base Attack"));
	if (Weapon != nullptr)
	{
		Weapon->Fire();
	}
}

void ACharacterBase::Hit(int32 Damage, AActor* ByWho)
{
	//UE_LOG(LogTemp, Display, TEXT("Character Base OnHit"));

	CurHP -= Damage;
}


void ACharacterBase::IncreaseKillCount()
{
	UE_LOG(LogTemp, Display, TEXT("Character Base IncreaseKillCount"));
}

