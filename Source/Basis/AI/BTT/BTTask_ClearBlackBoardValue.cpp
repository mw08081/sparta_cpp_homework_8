// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTT/BTTask_ClearBlackBoardValue.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackBoardValue::UBTTask_ClearBlackBoardValue()
{
	NodeName = FString(TEXT("ClearBlackboardValue"));
}

EBTNodeResult::Type UBTTask_ClearBlackBoardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* OwnerBlackboardComp = OwnerComp.GetBlackboardComponent();
	if (OwnerBlackboardComp == nullptr) return EBTNodeResult::Failed;

	if (OwnerBlackboardComp->IsVectorValueSet(GetSelectedBlackboardKey()))
	{
		OwnerBlackboardComp->ClearValue(GetSelectedBlackboardKey());
	}

	return EBTNodeResult::Succeeded;
}
