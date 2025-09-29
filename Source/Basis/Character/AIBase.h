// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "AIBase.generated.h"

/**
 * 
 */
UCLASS()
class BASIS_API AAIBase : public ACharacterBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

public:
	virtual void Attack();
	virtual void Hit(int32 Damage, AActor* ByWho);
	virtual void IncreaseKillCount();
};
