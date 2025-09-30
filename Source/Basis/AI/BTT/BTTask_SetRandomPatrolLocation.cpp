// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTT/BTTask_SetRandomPatrolLocation.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

UBTTask_SetRandomPatrolLocation::UBTTask_SetRandomPatrolLocation()
{
	NodeName = FString(TEXT("SetRandomPatrolLocation"));
}

EBTNodeResult::Type UBTTask_SetRandomPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* OwnerBlackboard = OwnerComp.GetBlackboardComponent();
	if (OwnerBlackboard == nullptr) return EBTNodeResult::Failed;

	if (OwnerBlackboard->IsVectorValueSet(GetSelectedBlackboardKey()))
	{
		return EBTNodeResult::Succeeded;
	}
	else
	{
		UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
		if (NavSystem == nullptr) return EBTNodeResult::Failed;

		FNavLocation LOC;
		NavSystem->GetRandomPoint(LOC);

		//DrawDebugSphere(GetWorld(), LOC.Location, 25, 25, FColor::Red, true);
		OwnerBlackboard->SetValueAsVector(GetSelectedBlackboardKey(), LOC.Location);

		return EBTNodeResult::Succeeded;
	}
}
