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

public:	
	virtual void Fire();
	
	UPROPERTY(EditAnywhere)
	int32 WeaponRpm = 500;


};
