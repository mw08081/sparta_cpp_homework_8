// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTS/BTService_FindTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Character/CharacterBase.h"

UBTService_FindTarget::UBTService_FindTarget()
{
	NodeName = FString(TEXT("FindTarget"));
}

void UBTService_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* OwnerBlackboard = OwnerComp.GetBlackboardComponent();
	if (OwnerBlackboard == nullptr) return;

	AAIController* MyController = OwnerComp.GetAIOwner();
	if (MyController == nullptr) return;

	ACharacterBase* MyPawn = Cast<ACharacterBase>(MyController->GetPawn());
	if (MyPawn == nullptr) return;

	ACharacterBase* TargetPawn = Cast<ACharacterBase>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (TargetPawn == nullptr) return;

	// 시야범위 안에 있는지 검사
	FVector ToTargetVector = TargetPawn->GetActorLocation() - MyPawn->GetActorLocation();
	if (ToTargetVector.Length() > SightRange)
	{
		if (OwnerBlackboard->IsVectorValueSet(GetSelectedBlackboardKey()) && !OwnerBlackboard->IsVectorValueSet(FName(TEXT("PatrolLocation"))))
		{
			FVector LastTargetLocation = OwnerBlackboard->GetValueAsVector(GetSelectedBlackboardKey());
			OwnerBlackboard->SetValueAsVector(FName(TEXT("PatrolLocation")), LastTargetLocation);

			OwnerBlackboard->ClearValue(GetSelectedBlackboardKey());
		}
		return;
	}

	// 시야각 안에 있는지 검사 
	FVector MyForwardVector = MyPawn->GetActorForwardVector();
	MyForwardVector.Normalize();
	ToTargetVector.Normalize();

	float DotRes = MyForwardVector.Dot(ToTargetVector);
	bool IsInSight = SightDegree > FMath::RadiansToDegrees(FMath::Acos(DotRes));
	if (!IsInSight) 
	{
		if (OwnerBlackboard->IsVectorValueSet(GetSelectedBlackboardKey()) && !OwnerBlackboard->IsVectorValueSet(FName(TEXT("PatrolLocation"))))
		{
			FVector LastTargetLocation = OwnerBlackboard->GetValueAsVector(GetSelectedBlackboardKey());
			OwnerBlackboard->SetValueAsVector(FName(TEXT("PatrolLocation")), LastTargetLocation);

			OwnerBlackboard->ClearValue(GetSelectedBlackboardKey());
		}
		return;
	}

	// 장애물 판단
	if (!MyController->LineOfSightTo(TargetPawn))
	{
		if(OwnerBlackboard->IsVectorValueSet(GetSelectedBlackboardKey()) && !OwnerBlackboard->IsVectorValueSet(FName(TEXT("PatrolLocation"))))
		{
			FVector LastTargetLocation = OwnerBlackboard->GetValueAsVector(GetSelectedBlackboardKey());
			OwnerBlackboard->SetValueAsVector(FName(TEXT("PatrolLocation")), LastTargetLocation);

			OwnerBlackboard->ClearValue(GetSelectedBlackboardKey());
		}
		return;
	}

	OwnerBlackboard->SetValueAsVector(GetSelectedBlackboardKey(), TargetPawn->GetActorLocation());
	OwnerBlackboard->ClearValue(FName(TEXT("PatrolLocation")));
	//DrawDebugSphere(GetWorld(), TargetPawn->GetActorLocation(), 25, 25, FColor::Blue, false, 1.0f);
}


