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
	TSubclassOf<class UStartGameWidget> StartGameWidget_class;
	class UStartGameWidget* StartGameWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UEndGameWidget> EndGameWidget_class;
	class UEndGameWidget* EndGameWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UMainHUD> MainHUD_class;
	class UMainHUD* MainHUD;

	int32 StageLv = 0;
	FTimerHandle StageStartHandle;

public:
	APlayerController* PlayerController;

	// for umg
	void SetPlayerKillCount(int32 Killcount);
	void SetPlayerHP(float HP);
	void SetWeaponAmmo(int32 WeaponAmmo);
	void SetPlayerAmmo(int32 PlayerAmmo);

private:
	UPROPERTY(EditDefaultsOnly)
	float StageLimitTime = 60;
	FTimerHandle StageTimeManageHandle;
	FTimerHandle StageTimeUpdateHandle;

	void EndStageTime();
	void UpdateStageTime();

public:

	TArray<int32> EnemyCntList = { 5, 7, 10 };
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ACharacterBase> EmemyClass;

	void ReadyGame();
	void StartGame();
	void EndGame(bool IsClear);

	int32 CurKilledEnemyCnt = 0;
	void KillEnemy();
};
 