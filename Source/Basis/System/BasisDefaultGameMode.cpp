// Fill out your copyright notice in the Description page of Project Settings.


#include "System/BasisDefaultGameMode.h"

#include "Blueprint/UserWidget.h"

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

