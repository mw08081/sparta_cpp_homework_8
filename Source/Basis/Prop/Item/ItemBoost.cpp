// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Item/ItemBoost.h"

#include "TimerManager.h"

#include "Character/CharacterBase.h"

void AItemBoost::Boost()
{
	ElapsedTime++;
	if (ElapsedTime > Duration) {
		GetWorld()->GetTimerManager().ClearTimer(BoostHandle);
		Destroy();
	}
	else
	{
		if (Taker == nullptr) return;
		
		int32 NewHP = FMath::Min(Taker->GetCurHP() + BoostAmount / Duration, Taker->MaxHP);
		Taker->SetCurHP(NewHP);
	}
}

void AItemBoost::OnItemTaken(AActor* TakerActor)
{
	// 바로 제거되지 않음
	// Suerp::OnItemTaken() 
	
	// Taker설정
	Taker = static_cast<ACharacterBase*>(TakerActor);

	// set unvisible
	SetActorHiddenInGame(true);

	// Start Timer
	ElapsedTime = 0;
	GetWorld()->GetTimerManager().SetTimer(BoostHandle, this, &AItemBoost::Boost, 1, true);
}
