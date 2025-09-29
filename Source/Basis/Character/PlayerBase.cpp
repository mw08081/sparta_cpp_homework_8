// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerBase.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

#include "AI/AIControllerBase.h"

#include "System/BasisDefaultGameMode.h"
#include "Weapon/WeaponBase.h"
#include "Character/CharacterBase.h"

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
	if (IsValid(PlayerController)) 
	{
		ULocalPlayer* Player = PlayerController->GetLocalPlayer();
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	CameraBoom->TargetArmLength = 100;
	CameraBoom->SocketOffset = FVector(4, 30, 80);

	Weapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass);
	if (IsValid(Weapon))
	{
		FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
		Weapon->AttachToComponent(GetMesh(), TransformRules, TEXT("WeaponSocket"));
		Weapon->SetOwner(this);

		Weapon->SetActorRelativeLocation(FVector(-0.223613, -6.477133, -2.791346));
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
		
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Started, this, &APlayerBase::Zoom);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Completed, this, &APlayerBase::Zoom);

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &APlayerBase::EnterFire);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, (void (APlayerBase::*)(const FInputActionValue&)) &APlayerBase::ExitFire);

		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &APlayerBase::Reload);
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

	if (Controller != nullptr) 
	{
		AddControllerYawInput(LookAxis.X);
		AddControllerPitchInput(LookAxis.Y * -1);
	}
}

void APlayerBase::Zoom(const FInputActionValue& Value)
{
	if (!IsValid(CameraBoom)) return;
	bool OnMouseButtonDown = Value.Get<bool>();


	if (OnMouseButtonDown)
	{
		CameraBoom->TargetArmLength = 35;
		CameraBoom->SocketOffset = FVector(4, 30, 80);
	}
	else
	{ 
		CameraBoom->TargetArmLength = 100;
		CameraBoom->SocketOffset = FVector(4, 30, 80);
	}
}


void APlayerBase::EnterFire(const FInputActionValue& Value)
{
	if (Weapon == nullptr) return;
	if (bCanAttack == false) return;

	const float FireInterval = Weapon->GetFireInterval();
	GetWorld()->GetTimerManager().SetTimer(FireHandle, this, &APlayerBase::Attack, FireInterval, true);
}


void APlayerBase::ExitFire(const FInputActionValue& Value)
{
	GetWorld()->GetTimerManager().ClearTimer(FireHandle);
}

void APlayerBase::ExitFire()
{
	GetWorld()->GetTimerManager().ClearTimer(FireHandle);
}

void APlayerBase::Reload(const FInputActionValue& Value)
{
	// 무기가 없으면 reload 불가
	if (Weapon == nullptr) return;

	// 장탄수 최대일 경우 reload 불가
	if (Weapon->GetMaxAmmoCapacity() == Weapon->GetCurAmmo()) return;

	// 보유 탄약수가 없으면 reload 불가
	if (AmmoCount < 1) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance == nullptr) return;

	// 사격 중지
	ExitFire();
	SetCanAttack(false);
	
	// Nofiy -> Weapon->Reload && this->bCanAttack = true;
	AnimInstance->Montage_Play(AMM_Reload); 
}

void APlayerBase::Attack()
{
	// 1회성 공격인 Super::Attack()에 대해서 주석 처리.
	//Super::Attack(); 

	if (Weapon != nullptr)
	{
		bool FireRes = Weapon->Fire();
		if(FireRes) AddControllerPitchInput(FMath::FRandRange(-0.8f,-0.3f));
	}
}

void APlayerBase::Hit(int32 Damage, AActor* ByWho)
{
	Super::Hit(Damage, ByWho);

	CurGameMode->SetPlayerHP((float)CurHP / MaxHP);
	
	if (CurHP <= 0) 
	{
		Destroy();
		if (IsValid(Weapon))
		{
			Weapon->Destroy();
		}
	}
}

void APlayerBase::IncreaseKillCount()
{
	Super::IncreaseKillCount();

	CurGameMode->SetPlayerKillCount(KillCount);
}



