// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_AimTarget.generated.h"

/**
 * 
 */
UCLASS()
class BASIS_API UBTService_AimTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_AimTarget();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
