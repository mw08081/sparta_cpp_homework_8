// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BulletBase.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/DecalActor.h"

#include "Character/CharacterBase.h"

// Sets default values
ABulletBase::ABulletBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	//StaticMeshComponent->SetupAttachment(RootComponent);
	RootComponent = StaticMeshComponent;

	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	StaticMeshComponent->SetNotifyRigidBodyCollision(true);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 10000.0f;
	ProjectileMovementComponent->MaxSpeed = 10000.0f;
}

// Called when the game starts or when spawned
void ABulletBase::BeginPlay()
{ 
	Super::BeginPlay();

	StaticMeshComponent->OnComponentHit.AddDynamic(this, &ABulletBase::OnHit);
}

void ABulletBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* Weapon = GetOwner();

	if (!IsValid(Weapon)) return;

	ACharacterBase* WeaponOwner = Cast<ACharacterBase>(Weapon->GetOwner());
	if (!IsValid(WeaponOwner)) return;

	ACharacterBase* Target = Cast<ACharacterBase>(OtherActor);
	if (IsValid(Target)) {
		float Damage = WeaponOwner->Strength;

		if (Hit.BoneName.ToString().StartsWith("Head")) {
			Damage *= 1.2f;
			DrawDebugSphere(GetWorld(), Hit.Location, 1.5f, 24, FColor::Red, false, 3);
		}
		else if (Hit.BoneName.ToString().StartsWith("Spine")) {
			Damage *= 0.7f;
			DrawDebugSphere(GetWorld(), Hit.Location, 1.5f, 24, FColor::Yellow, false, 3);
		}
		else {
			Damage *= 0.4f;
			//DrawDebugSphere(GetWorld(), Hit.Location, 1.f, 24, FColor::Blue, false, 3);
		}
		
		//UE_LOG(LogTemp, Display, TEXT("%s hit: %s (%d) -> %d/%d"), *OtherActor->GetActorNameOrLabel(), *Hit.BoneName.ToString(), (int)Damage, Target->GetCurHP() - (int)Damage, Target->MaxHP);
		Target->Hit((int)Damage, WeaponOwner);
	}

	//FRotator DecalRotation = Hit.ImpactNormal.Rotation();
	//DecalRotation.Roll = FMath::FRand() * 360.f; // 무작위 회전으로 다양함 추가

	//// 데칼 스폰
	//UGameplayStatics::SpawnDecalAtLocation(
	//	GetWorld(),
	//	BulletDecalMaterial,
	//	FVector(10, 10, 10),
	//	Hit.ImpactPoint,
	//	DecalRotation,
	//	10.f
	//);

	//UE_LOG(LogTemp, Display, TEXT("spawn decal"));

	Destroy();
}