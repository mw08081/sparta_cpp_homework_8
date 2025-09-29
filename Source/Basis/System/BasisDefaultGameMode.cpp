// Fill out your copyright notice in the Description page of Project Settings.


#include "System/BasisDefaultGameMode.h"

#include "Blueprint/UserWidget.h"
#include "NavigationSystem.h"

#include "Character/CharacterBase.h"
#include "Widget/MainHUD.h"

void ABasisDefaultGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(MainHUD_class)) {
		MainHUD = CreateWidget<UUserWidget>(GetWorld(), MainHUD_class);

	}

	if (IsValid(MainHUD)) {
		MainHUD->AddToViewport();
	}
}

void ABasisDefaultGameMode::SetPlayerKillCount(int32 KillCount)
{
	PlayerKillCount = KillCount;
	Cast<UMainHUD>(MainHUD)->SetKillCount(PlayerKillCount);
}

void ABasisDefaultGameMode::SetPlayerHP(float HP)
{
	PlayerHP = HP;
	Cast<UMainHUD>(MainHUD)->SetHp(PlayerHP);
}

void ABasisDefaultGameMode::SetWeaponAmmo(int32 CurAmmo)
{
	Cast<UMainHUD>(MainHUD)->SetWeaponAmmo(CurAmmo);
}

void ABasisDefaultGameMode::SetPlayerAmmo(int32 PlayerAmmo)
{
	Cast<UMainHUD>(MainHUD)->SetPlayerAmmo(PlayerAmmo);
}

void ABasisDefaultGameMode::StartGame()
{
	UE_LOG(LogTemp, Display, TEXT("StartGame"));
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NavSystem == nullptr) return;


	int32 EmemyCnt = EmemyCntList[StageLv];
	UE_LOG(LogTemp, Display, TEXT("Generate ememy %d"), EmemyCnt);
	for (int32 i = 0; i < EmemyCnt; i++) {
		FNavLocation LOC;
		NavSystem->GetRandomPoint(LOC);

		GetWorld()->SpawnActor<ACharacterBase>(EmemyClass, LOC.Location, FRotator::ZeroRotator);
	}
}

