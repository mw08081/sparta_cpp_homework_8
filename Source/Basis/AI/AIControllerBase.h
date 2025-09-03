// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class BASIS_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	AAIControllerBase();

public:
	virtual void OnPossess(APawn* InPawn) override;

public:
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTreeComp = nullptr;
	
};
