// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BasisDefaultGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BASIS_API ABasisDefaultGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> MainHUD_class;

	UPROPERTY(VisibleAnywhere)
	class UUserWidget* MainHUD;

	int32 StageLv;

	/// <summary>
	/// Player Information
	/// When player call function, it will be updated
	/// </summary>
	int32 PlayerKillCount;
	float PlayerHP;

public:
	// for umg
	void SetPlayerKillCount(int32 Killcount);
	void SetPlayerHP(float HP);
	void SetWeaponAmmo(int32 WeaponAmmo);
	void SetPlayerAmmo(int32 PlayerAmmo);
};
