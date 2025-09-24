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
        
        if (Player->Weapon == nullptr) return;
        Player->Weapon->Reload();
    }
}
