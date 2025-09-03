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
	int32 Strength = 10;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 AttackCount = 0;

protected:
	int32 CurHP = 0;
	int32 KillCount = 0;

public:
	UPROPERTY(EditDefaultsOnly, Category = "weapon")
	TSubclassOf<class AWeaponBase> WeaponClass;

	UPROPERTY(VisibleAnywhere, Category = "weapon")
	class AWeaponBase* Weapon;

public:
	virtual void Attack();

	UFUNCTION(BlueprintCallable)
	virtual void Hit(int32 Damage, AActor* ByWho);

	UFUNCTION(BlueprintCallable)
	virtual void IncreaseKillCount();

};
