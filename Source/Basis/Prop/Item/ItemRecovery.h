// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Item/ItemBase.h"
#include "ItemRecovery.generated.h"

/**
 * 
 */
UCLASS()
class BASIS_API AItemRecovery : public AItemBase
{
	GENERATED_BODY()


private:
	UPROPERTY(EditAnywhere)
	int32 RecoveryAmount;

	UPROPERTY(EditAnywhere)
	int32 MaxRecoveryAmount;

protected:
	virtual void OnItemTaken(AActor* TakerActor) override;
};
