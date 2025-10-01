// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class BASIS_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    virtual void NativeConstruct() override;

protected:
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Txt_GameResult;

    UPROPERTY(meta = (BindWidget))
    class UButton* Btn_RestartGame;

    UFUNCTION()
    void OnClickRestartGame();

public:
    UFUNCTION()
    void SetTxtGameResult(bool IsClear);
};
