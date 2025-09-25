// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Item/ItemAmmo.h"

#include "Character/PlayerBase.h"
#include "Weapon/WeaponBase.h"

void AItemAmmo::OnItemTaken(AActor* TakerActor)
{
	Super::OnItemTaken(TakerActor);

	UE_LOG(LogTemp, Display, TEXT("ITEM AMMO OnItemTaken"));

	APlayerBase* TakerCharacter = Cast<APlayerBase>(TakerActor);
	if (TakerCharacter == nullptr) return;

	int32 CharacterAmmoCount = TakerCharacter->GetAmmoCount();
	TakerCharacter->SetAmmoCount(CharacterAmmoCount + AmmoCount);
}
