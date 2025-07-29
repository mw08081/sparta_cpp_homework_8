// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ChracterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BASIS_API UChracterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UFUNCTION()
	void AnimNotify_Attack();

	UPROPERTY(BlueprintReadOnly)
	class ACharacterBase* Character;

	UPROPERTY(BlueprintReadOnly)
	class UCharacterMovementComponent* MovementComponent;

	UPROPERTY(BlueprintReadOnly)
	FRotator ControllerRot;
	UPROPERTY(BlueprintReadOnly)
	FRotator ActorRot;

	UPROPERTY(BlueprintReadOnly)
	float Speed;

	UPROPERTY(BlueprintReadOnly)
	int32 AttackCount;

};
