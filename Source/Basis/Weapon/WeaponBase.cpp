// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"

#include "Kismet/KismetMathLibrary.h"

#include "Weapon/BulletBase.h"
#include "Character/CharacterBase.h"
#include "Character/PlayerBase.h"
#include "System/BasisDefaultGameMode.h"

#include <AI/AIControllerBase.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	MuzzleOffset = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleOffset"));
	MuzzleOffset->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
	this->FireInterval = 60.0f / WeaponRpm;
	this->CurAmmo = MaxAmmoCapacity;

	GameMode = Cast<ABasisDefaultGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}


bool AWeaponBase::Fire()
{
	if (CurAmmo < 1) return false;

	UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
	if (IsValid(AnimInstance) && IsValid(FireAnimMontage)) {
		AnimInstance->Montage_Play(FireAnimMontage);
	}
	else {
		return false;
	}

	if (IsValid(BulletClass)) {
		FRotator SpawnRotation = MuzzleOffset->GetComponentRotation();
		FVector SpawnLocation = MuzzleOffset->GetComponentLocation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		// APlayerBase로 캐스팅 하면 안되나? Enemy가 총을 쏠 수 있잖아..
		// PlayerController->GetViewportSize(x, y); 이래.. 그럼 이것도 오버라이딩해서 에너미랑 플레이어로 구분하는게 좋을듯.. 
		ACharacterBase* WeaponOwner = Cast<APlayerBase>(GetOwner());
		if (!IsValid(WeaponOwner)) return false;

		AController* WeaponOwnerController = WeaponOwner->GetController();
		if (!IsValid(WeaponOwner)) return false;


		if (APlayerController* PlayerController = Cast<APlayerController>(WeaponOwnerController))
		{
			int32 x, y;
			PlayerController->GetViewportSize(x, y);

			// WorldCenter의 존재 이유가 뭘까???
			FVector WorldCenter;
			FVector WorldFront;
			PlayerController->DeprojectScreenPositionToWorld(x * 0.5f, y * 0.5f, WorldCenter, WorldFront);

			//UE_LOG(LogTemp, Display, TEXT("World Center: %s"), *WorldCenter.ToCompactString());

			WorldCenter += WorldFront * 10000;
			SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, WorldCenter);

			GetWorld()->SpawnActor<ABulletBase>(BulletClass, SpawnLocation, SpawnRotation, SpawnParams);

			CurAmmo--;

			if (GameMode == nullptr) return false;
			GameMode->SetWeaponAmmo(CurAmmo, MaxAmmoCapacity);
		} 
		else if (AAIControllerBase* AIController = Cast<AAIControllerBase>(WeaponOwnerController))
		{
			APawn* TargetPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

			SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, TargetPawn->GetActorLocation());
			GetWorld()->SpawnActor<ABulletBase>(BulletClass, SpawnLocation, SpawnRotation, SpawnParams);
		}

	}
	else {
		return false;
	}

	return true;
}

void AWeaponBase::Reload()
{
	GetWorld()->GetTimerManager().SetTimer(ReloadHandle, this, &AWeaponBase::ExecReload, ReloadDelay, false);
}

void AWeaponBase::ExecReload()
{
	this->CurAmmo = this->MaxAmmoCapacity;
	GameMode->SetWeaponAmmo(CurAmmo, MaxAmmoCapacity);
}

float AWeaponBase::GetFireInterval() const
{
	return this->FireInterval;
}





