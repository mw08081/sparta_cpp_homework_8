// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ChracterAnimInstance.h"

#include "Character/CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UChracterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ACharacterBase>(TryGetPawnOwner());
	if (IsValid(Character)) {
		MovementComponent = Character->GetCharacterMovement();
	}
}

void UChracterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(MovementComponent)) {
		Speed = MovementComponent->Velocity.Size();
		AttackCount = Character->AttackCount;
	}

	if (IsValid(Character)) {
		ActorRot = Character->GetActorRotation();
		ControllerRot = Character->GetControlRotation();
	}
}

void UChracterAnimInstance::AnimNotify_Attack()
{
	Character->AttackCount = 0;
	AttackCount = 0;
}
