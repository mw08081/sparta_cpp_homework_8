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
	class UUserWidget* MainHUD;

	int32 StageLv = 0;

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

public:
	TArray<int32> EmemyCntList = { 5, 7, 10 };
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ACharacterBase> EmemyClass;

	UFUNCTION(BlueprintCallable)
	void StartGame();
};
