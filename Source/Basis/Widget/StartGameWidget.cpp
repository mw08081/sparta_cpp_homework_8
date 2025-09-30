// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/StartGameWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

#include "System/BasisDefaultGameMode.h"

void UStartGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_StartGame != nullptr) {
		Btn_StartGame->OnClicked.AddDynamic(this, &UStartGameWidget::OnClickStartGame);
	}
}

void UStartGameWidget::OnClickStartGame()
{
	ABasisDefaultGameMode* GameMode = static_cast<ABasisDefaultGameMode*>(UGameplayStatics::GetGameMode(GetWorld()));
	
	if (GameMode == nullptr) return;
	GameMode->CreateMainHUD();
}
