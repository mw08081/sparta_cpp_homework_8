// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Item/ItemBase.h"
#include "ItemBoost.generated.h"

/**
 * 
 */
UCLASS()
class BASIS_API AItemBoost : public AItemBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	int32 BoostAmount;
	UPROPERTY(EditAnywhere)
	int32 Duration;

	int32 ElapsedTime;

	FTimerHandle BoostHandle;
	class ACharacterBase* Taker = nullptr;

private:
	void Boost();

protected:
	virtual void OnItemTaken(AActor* TakerActor) override;
};
