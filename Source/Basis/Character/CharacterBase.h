// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class BASIS_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	class ABasisDefaultGameMode* CurGameMode;

public:
	UPROPERTY(EditAnywhere)
	int32 MaxHP = 100;

	UPROPERTY(EditAnywhere)
	int32 Strength = 30;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 AttackCount = 0;

protected:
	int32 AmmoCount = 42;
	int32 CurHP = 0;
	int32 KillCount = 0;

public:
	UPROPERTY(EditDefaultsOnly, Category = "weapon")
	TSubclassOf<class AWeaponBase> WeaponClass;

	UPROPERTY(VisibleAnywhere, Category = "weapon")
	class AWeaponBase* Weapon;

protected:
	bool bCanAttack = true;

public:
	bool GetCanAttack() const;
	void SetCanAttack(bool _bCanAttack);
	
	int32 GetAmmoCount() const;
	void SetAmmoCount(int32 AmmoCount);

	int32 GetCurHP() const;
	void SetCurHP(int32 _HP);

	virtual void Attack();
	virtual void Hit(int32 Damage, AActor* ByWho);
	virtual void IncreaseKillCount();

};
