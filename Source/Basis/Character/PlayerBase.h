// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "PlayerBase.generated.h"

/**
 * 
 */
UCLASS()
class BASIS_API APlayerBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	APlayerBase();

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputController) override;
	
	virtual void Attack() override;
	virtual void Hit(int32 Damage, AActor* ByWho) override;
	virtual void IncreaseKillCount() override;

private:

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly)
	class UInputMappingContext* InputMappingContext;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* LookAction;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* FireAction;
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* ZoomAction;

	void Move(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);
	void Fire(const struct FInputActionValue& Value);
	void Zoom(const struct FInputActionValue& Value);

};
