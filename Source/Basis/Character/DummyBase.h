// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "DummyBase.generated.h"

/**
 * 
 */
UCLASS()
class BASIS_API ADummyBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime);
	
private:
	UPROPERTY(EditAnywhere)
	FVector MovingDirection;
	UPROPERTY(EditAnywhere)
	float MovingDistance;
	UPROPERTY(EditAnywhere)
	float MovingSpeed;

	bool IsMoveToTarget = true;
	float CurMovingDist = 0;
	FVector OrgLocation;
	FVector TargetLocation;

	void Moving(float DeltaTime);

private:
	FTimerHandle AutoReturnHandle;

	bool IsPositiveSide = true;
	bool IsShouldRot = false;

	FRotator RotDirection = FRotator(0,0,1);
	float RotSpeed = 720;

	FRotator OrgRot;
	FRotator TargetRot;
	float CurRotAmmount;

	void ExecRot();
	void Rotating(float DeltaTime);

public:
	UFUNCTION(BlueprintCallable)
	virtual void Hit(int32 Damage, AActor* ByWho);
};
