// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Attack.generated.h"

/**
 * 
 */
UCLASS()
class BASIS_API UBTT_Attack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_Attack();

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& BTC, uint8* NodeMemory) override;;


};
