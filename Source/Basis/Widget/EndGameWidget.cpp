// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EndGameWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "Kismet/GameplayStatics.h"

#include "System/BasisDefaultGameMode.h"

void UEndGameWidget::NativeConstruct()
{
	if (Btn_RestartGame == nullptr) return;
	Btn_RestartGame->OnClicked.AddDynamic(this, &UEndGameWidget::OnClickRestartGame);
}

void UEndGameWidget::SetTxtGameResult(bool IsClear)
{
	if (Txt_GameResult == nullptr) return;

	if (IsClear) {
		Txt_GameResult->SetText(FText::FromString(FString(TEXT("Clear!!"))));
	}
	else {
		Txt_GameResult->SetText(FText::FromString(FString(TEXT("Retry???"))));
	}
}

void UEndGameWidget::OnClickRestartGame()
{
	//static_cast<ABasisDefaultGameMode*>(UGameplayStatics::GetGameMode(GetWorld()))->ReadyGame();
	FName CurLevelName = FName(GetWorld()->GetName());
	UGameplayStatics::OpenLevel(GetWorld(), CurLevelName);
}
