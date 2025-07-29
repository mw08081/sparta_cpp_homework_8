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
