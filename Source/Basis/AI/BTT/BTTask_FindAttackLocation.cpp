// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTT/BTTask_FindAttackLocation.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_FindAttackLocation::UBTTask_FindAttackLocation()
{
	NodeName = FString(TEXT("FindAttackPosition"));
}

EBTNodeResult::Type UBTTask_FindAttackLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* OwnerBlackboard = OwnerComp.GetBlackboardComponent();
	if (OwnerBlackboard == nullptr) return EBTNodeResult::Failed;

	FVector TargetLocation = OwnerBlackboard->GetValueAsVector(GetSelectedBlackboardKey());
	DrawDebugCircle(GetWorld(), TargetLocation, 900.f, 25, FColor::Yellow, false, 3.0f, 0, 2.0f, FVector(0, 1, 0), FVector(1, 0, 0), false);

	float Radius = FMath::RandRange(100 * 6, 100 * 9);
	float Degree = FMath::RandRange(0.0f, 360.0f);

	TargetLocation = TargetLocation + FVector(FMath::Cos(Degree), FMath::Sin(Degree), 0) * Radius;
	
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NavSystem == nullptr) return EBTNodeResult::Failed;

	FNavLocation LOC;
	NavSystem->ProjectPointToNavigation(TargetLocation, LOC);
	DrawDebugSphere(GetWorld(), LOC.Location, 25, 25, FColor::Green, true);

	OwnerBlackboard->SetValueAsVector(FName(TEXT("AttackLocation")), LOC.Location);

	return EBTNodeResult::Succeeded;
}


