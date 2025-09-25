// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Item/ItemBase.h"

#include "Character/CharacterBase.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnComponentBeginOverlap);
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacterBase* Player = Cast<ACharacterBase>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ACharacterBase* Overlap = Cast<ACharacterBase>(OtherActor);
	if (Player != Overlap) return;
	
	OnItemTaken(OtherActor);
}

void AItemBase::OnItemTaken(AActor* TakerActor)
{
	Destroy();
}

