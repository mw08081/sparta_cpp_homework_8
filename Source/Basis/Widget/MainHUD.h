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
	class UTextBlock* Txt_KillCount;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_StageLv;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_CurAmmo;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_MaxAmmo;

	UFUNCTION()
	void SetHp(float Value);

	UFUNCTION()
	void SetKillCount(int32 Value);

	UFUNCTION()
	void SetStageLv(int32 Value);

	UFUNCTION()
	void SetWeaponAmmo(int32 CurAmmo, int32 MaxAmmo);
		
};
