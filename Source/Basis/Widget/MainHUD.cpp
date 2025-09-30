// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainHUD.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMainHUD::SetHp(float Value)
{
	if (IsValid(PB_HPGauge)) {
		PB_HPGauge->SetPercent(Value);
	}
}

void UMainHUD::SetStageTime(float Value)
{
	if (Txt_StageTime != nullptr) {
		Txt_StageTime->SetText(FText::FromString(FString::Printf(TEXT("%d"), static_cast<int32>(Value))));
	}
}

void UMainHUD::SetKillCount(int32 Value)
{
	if (IsValid(Txt_KillCount))
	{
		Txt_KillCount->SetText(FText::FromString(FString::Printf(TEXT("Kill: %d"), Value)));
	}
}

void UMainHUD::SetStageLv(int32 Value)
{
	if (IsValid(Txt_StageLv)) {
		Txt_StageLv->SetText(FText::FromString(FString::Printf(TEXT("Stage Level: %d"), Value)));
	}
}

void UMainHUD::SetWeaponAmmo(int32 WeaponAmmo)
{
	if (Txt_WeaponAmmo != nullptr) {
		Txt_WeaponAmmo->SetText(FText::FromString(FString::Printf(TEXT("%d"), WeaponAmmo)));
	}
}

void UMainHUD::SetPlayerAmmo(int32 PlayerAmmo)
{
	if (Txt_PlayerAmmo != nullptr) {
		Txt_PlayerAmmo->SetText(FText::FromString(FString::Printf(TEXT("%d"), PlayerAmmo)));
	}
}
