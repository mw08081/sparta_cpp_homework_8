// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTT/BTTask_InitAI.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTTask_InitAI::UBTTask_InitAI()
{
	NodeName = TEXT("InitAI");
}

EBTNodeResult::Type UBTTask_InitAI::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (BB == nullptr) return EBTNodeResult::Failed;

	if (BB->IsVectorValueSet(GetSelectedBlackboardKey()) == false)
	{
		BB->SetValueAsVector(GetSelectedBlackboardKey(), OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation());
	}
	return EBTNodeResult::Succeeded;
}
