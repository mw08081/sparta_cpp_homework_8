// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIControllerBase.h"

AAIControllerBase::AAIControllerBase()
{

}

void AAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTreeComp == nullptr) return;

	RunBehaviorTree(BehaviorTreeComp);
}
