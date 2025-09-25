// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class BASIS_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* MuzzleOffset;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* FireAnimMontage;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABulletBase> BulletClass;

private:
	class ABasisDefaultGameMode* GameMode;

private:
	UFUNCTION()
	void ExecReload(int32 AmmoCount);

public:	
	int32 GetMaxAmmoCapacity() const;
	int32 GetCurAmmo() const;

	virtual bool Fire();
	virtual void Reload(int32 AmmoCount);
	
	float GetFireInterval() const;

private:
	UPROPERTY(EditDefaultsOnly)
	int32 MaxAmmoCapacity = 30;
	int32 CurAmmo;

	UPROPERTY(EditDefaultsOnly)
	float ReloadDelay = 0.3f;
	FTimerHandle ReloadHandle;

public:
	UPROPERTY(EditDefaultsOnly)
	int32 WeaponRpm = 500;
	float FireInterval = 0.1f;

};
