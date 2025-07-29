// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerBase.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

#include "System/BasisDefaultGameMode.h"
#include "Weapon/WeaponBase.h"

APlayerBase::APlayerBase()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
}

void APlayerBase::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (IsValid(PlayerController)) {
		ULocalPlayer* Player = PlayerController->GetLocalPlayer();
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player)) {
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	CameraBoom->TargetArmLength = 120;
	CameraBoom->SocketOffset = FVector(0, 60, 60);

	Weapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass);
	if (IsValid(Weapon)) {
		FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
		Weapon->AttachToComponent(GetMesh(), TransformRules, TEXT("WeaponSocket"));
		Weapon->SetOwner(this);
	}

	CurGameMode->SetPlayerHP(CurHP / MaxHP);
}

void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputController)
{
	Super::SetupPlayerInputComponent(PlayerInputController);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast< UEnhancedInputComponent>(PlayerInputController))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerBase::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerBase::Look);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &APlayerBase::Fire);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &APlayerBase::Zoom);
	}
}

void APlayerBase::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APlayerBase::Look(const FInputActionValue& Value)
{
	FVector2d LookAxis = Value.Get<FVector2D>();

	if (Controller != nullptr) {
		AddControllerYawInput(LookAxis.X);
		AddControllerPitchInput(LookAxis.Y * -1);
	}
}

void APlayerBase::Fire(const FInputActionValue& Value)
{
	Attack();
}

void APlayerBase::Zoom(const FInputActionValue& Value)
{
	if (!IsValid(CameraBoom)) return;
	float WheelDirection = Value.Get<float>();


	if (WheelDirection > 0) {
		CameraBoom->TargetArmLength = 40;
		CameraBoom->SocketOffset = FVector(0, 40, 60);
	}
	else {
		CameraBoom->TargetArmLength = 120;
		CameraBoom->SocketOffset = FVector(0, 60, 60);
	}
}


void APlayerBase::Attack()
{
	Super::Attack();

	if (IsValid(Weapon)) {
		Weapon->Fire();
	}
}

void APlayerBase::Hit(int32 Damage, AActor* ByWho)
{
	Super::Hit(Damage, ByWho);

	if (CurHP <= 0) {
		CurHP = 0;
	}

	CurGameMode->SetPlayerHP((float)CurHP / MaxHP);

	if (CurHP <= 0) {
		Destroy();
	}
}

void APlayerBase::IncreaseKillCount()
{
	Super::IncreaseKillCount();

	KillCount += 1;
	CurGameMode->SetPlayerKillCount(KillCount);
}



