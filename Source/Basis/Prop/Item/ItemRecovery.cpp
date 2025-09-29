// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Item/ItemRecovery.h"

#include "Character/PlayerBase.h"

void AItemRecovery::OnItemTaken(AActor* TakerActor)
{
	Super::OnItemTaken(TakerActor);

	APlayerBase* TakerCharacter = Cast<APlayerBase>(TakerActor);
	if (TakerCharacter == nullptr) return;

	int32 PlayerHP = TakerCharacter->GetCurHP();
	
	// 테스트 코드
	if (PlayerHP >= MaxRecoveryAmount && RecoveryAmount > 0) return;
	//if (PlayerHP >= MaxRecoveryAmount) return;

	TakerCharacter->SetCurHP(FMath::Min(PlayerHP + RecoveryAmount, MaxRecoveryAmount));
}
