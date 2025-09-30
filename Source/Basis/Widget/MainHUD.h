// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class BASIS_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HPGauge;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_StageTime;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_KillCount;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_StageLv;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_WeaponAmmo;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_PlayerAmmo;

	UFUNCTION()
	void SetHp(float Value);

	UFUNCTION()
	void SetStageTime(float Value);

	UFUNCTION()
	void SetKillCount(int32 Value);

	UFUNCTION()
	void SetStageLv(int32 Value);

	UFUNCTION()
	void SetWeaponAmmo(int32 WeaponAmmo);
		
	UFUNCTION()
	void SetPlayerAmmo(int32 PlayerAmmo);
};
