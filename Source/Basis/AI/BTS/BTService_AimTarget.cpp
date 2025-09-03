// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTS/BTService_AimTarget.h"

#include "Kismet/KismetMathLibrary.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "Character/CharacterBase.h"

UBTService_AimTarget::UBTService_AimTarget()
{
	NodeName = FString(TEXT("AimTarget"));
}

void UBTService_AimTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (BlackBoardComp == nullptr) return;

	AAIController* MyController = OwnerComp.GetAIOwner();
	if (MyController == nullptr) return;

	ACharacterBase* MyCharacter = Cast<ACharacterBase>(MyController->GetPawn());
	if (MyCharacter == nullptr) return;

	if (BlackBoardComp->IsVectorValueSet(GetSelectedBlackboardKey()))
	{
		FVector ToTargetVector = BlackBoardComp->GetValueAsVector(GetSelectedBlackboardKey()) - MyCharacter->GetActorLocation();
		MyCharacter->SetActorRotation(ToTargetVector.Rotation());
	}
}
	