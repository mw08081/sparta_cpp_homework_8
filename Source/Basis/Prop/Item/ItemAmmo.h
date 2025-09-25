// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Item/ItemBase.h"
#include "ItemAmmo.generated.h"

/**
 * 
 */
UCLASS()
class BASIS_API AItemAmmo : public AItemBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	int32 AmmoCount;

protected:
	virtual void OnItemTaken(AActor* Taker) override;
};
