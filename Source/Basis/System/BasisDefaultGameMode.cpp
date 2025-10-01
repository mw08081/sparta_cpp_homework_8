// Fill out your copyright notice in the Description page of Project Settings.


#include "System/BasisDefaultGameMode.h"

#include "Blueprint/UserWidget.h"
#include "NavigationSystem.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

#include "Character/CharacterBase.h"
#include "Widget/MainHUD.h"
#include "Widget/StartGameWidget.h"
#include "Widget/EndGameWidget.h"

void ABasisDefaultGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();
	
	if (PlayerController == nullptr) return;
	PlayerController->bShowMouseCursor = true;
	PlayerController->SetInputMode(FInputModeUIOnly());

	if (StartGameWidget_class == nullptr) return;
	StartGameWidget = CreateWidget<UStartGameWidget>(GetWorld(), StartGameWidget_class);
	
	if (StartGameWidget == nullptr) return;
	StartGameWidget->AddToViewport();	
}

void ABasisDefaultGameMode::SetPlayerKillCount(int32 KillCount)
{
	if (MainHUD == nullptr) return;
	MainHUD->SetKillCount(KillCount);
}

void ABasisDefaultGameMode::SetPlayerHP(float HP)
{
	if (MainHUD == nullptr) return;
	MainHUD->SetHp(HP);
}

void ABasisDefaultGameMode::SetWeaponAmmo(int32 CurAmmo)
{
	if (MainHUD == nullptr) return;
	MainHUD->SetWeaponAmmo(CurAmmo);
}

void ABasisDefaultGameMode::SetPlayerAmmo(int32 PlayerAmmo)
{
	if (MainHUD == nullptr) return;
	MainHUD->SetPlayerAmmo(PlayerAmmo);
}

void ABasisDefaultGameMode::EndStageTime()
{
	if (PlayerController == nullptr) return;
	ACharacterBase* PlayerCharacter = static_cast<ACharacterBase*>(PlayerController->GetCharacter());
	PlayerCharacter->Hit(100, PlayerCharacter);

	EndGame(false);
}

void ABasisDefaultGameMode::UpdateStageTime()
{
	FTimerManager& WorldTimerManager = GetWorld()->GetTimerManager();
	int32 CurElapsedTime = static_cast<int32>(WorldTimerManager.GetTimerElapsed(StageTimeManageHandle));

	if (MainHUD == nullptr) return;
	MainHUD->SetStageTime(StageLimitTime - CurElapsedTime);
}

void ABasisDefaultGameMode::ReadyGame()
{
	if (StartGameWidget == nullptr) return;
	if (StartGameWidget->IsInViewport()) {
		StartGameWidget->RemoveFromParent();
	}

	if (EndGameWidget != nullptr && EndGameWidget->IsInViewport()) {
		EndGameWidget->RemoveFromParent();
	}

	if (MainHUD_class == nullptr) return;
	MainHUD = CreateWidget<UMainHUD>(GetWorld(), MainHUD_class);
	
	if (MainHUD == nullptr)  return;
	MainHUD->AddToViewport();
	
	if (PlayerController == nullptr) return;
	PlayerController->bShowMouseCursor = false;
	PlayerController->SetInputMode(FInputModeGameOnly());

	StageLv = 0;
	StartGame();
}

void ABasisDefaultGameMode::StartGame()
{
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NavSystem == nullptr) return;

	CurKilledEnemyCnt = 0;

	int32 EnemyCnt = EnemyCntList[StageLv];
	for (int32 i = 0; i < EnemyCnt; i++) {
		FNavLocation LOC;
		NavSystem->GetRandomPoint(LOC);

		GetWorld()->SpawnActor<ACharacterBase>(EmemyClass, LOC.Location, FRotator::ZeroRotator);
	}

	GetWorld()->GetTimerManager().SetTimer(StageTimeManageHandle, this, &ABasisDefaultGameMode::EndStageTime, StageLimitTime, false);
	GetWorld()->GetTimerManager().SetTimer(StageTimeUpdateHandle, this, &ABasisDefaultGameMode::UpdateStageTime, 1, true);
	UE_LOG(LogTemp, Display, TEXT("Wave %d!!"), StageLv + 1);
}

void ABasisDefaultGameMode::EndGame(bool IsClear)
{
	GetWorld()->GetTimerManager().ClearTimer(StageTimeUpdateHandle);

	if (PlayerController == nullptr) return;
	PlayerController->bShowMouseCursor = true;
	PlayerController->SetInputMode(FInputModeUIOnly());

	if (EndGameWidget_class == nullptr) return;
	EndGameWidget = CreateWidget<UEndGameWidget>(GetWorld(), EndGameWidget_class);

	if (EndGameWidget == nullptr) return;
	EndGameWidget->SetTxtGameResult(IsClear);
	EndGameWidget->AddToViewport();
}

void ABasisDefaultGameMode::KillEnemy()
{
	CurKilledEnemyCnt++;

	if (EnemyCntList[StageLv] == CurKilledEnemyCnt) {
		if (StageLv >= 2) {
			UE_LOG(LogTemp, Display, TEXT("Game Clear!!"));
			EndGame(true);
		}
		else {
			UE_LOG(LogTemp, Display, TEXT("Stage END!!"));
			StageLv++;

			GetWorld()->GetTimerManager().SetTimer(StageStartHandle, this, &ABasisDefaultGameMode::StartGame, 3, false);
		}
	}
}

