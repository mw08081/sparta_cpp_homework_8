// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AN_ReloadComplete.h"

#include "GameFramework/Actor.h"

#include "Character/PlayerBase.h"
#include "Weapon/WeaponBase.h"

void UAN_ReloadComplete::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);

    if (MeshComp && MeshComp->GetOwner())
    {
        APlayerBase* Player = Cast<APlayerBase>(MeshComp->GetOwner());
        if (Player == nullptr) return;

        Player->SetCanAttack(true);
        
        AWeaponBase* OwnerWeapon = Player->Weapon;
        if (OwnerWeapon == nullptr) return;
        int32 PlayerAmmoCount = Player->GetAmmoCount();
        int32 ReloadAmount = FMath::Min(PlayerAmmoCount, OwnerWeapon->GetMaxAmmoCapacity() - OwnerWeapon->GetCurAmmo());
        
        // call reload
        Player->Weapon->Reload(ReloadAmount);
        Player->SetAmmoCount(PlayerAmmoCount - ReloadAmount);
    }
}
