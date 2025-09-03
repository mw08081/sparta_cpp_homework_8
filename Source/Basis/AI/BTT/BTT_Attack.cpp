// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTT/BTT_Attack.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"

#include "Character/CharacterBase.h"

UBTT_Attack::UBTT_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& BTC, uint8* NodeMemory)
{
	UBlackboardComponent* BBC = BTC.GetBlackboardComponent();
	if (BBC == nullptr) return EBTNodeResult::Failed;

	// AI 검증
	AAIController* AIController = BTC.GetAIOwner();
	if (AIController == nullptr) return EBTNodeResult::Failed;

	//ACharacterBase* AIPawn = Cast<ACharacterBase>(BTC.GetOwner()); // 도 가능
	ACharacterBase* AIPawn = Cast<ACharacterBase>(AIController->GetPawn());
	if(AIPawn == nullptr) return EBTNodeResult::Failed;

	// Target Player 검증
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController == nullptr) return EBTNodeResult::Failed;

	ACharacterBase* TargetPawn = Cast<ACharacterBase>(PlayerController->GetPawn());
	if (TargetPawn == nullptr) return EBTNodeResult::Failed;
	 
	// 공격위치 설정
	AIController->StopMovement();

	AIPawn->Attack();

	return EBTNodeResult::Succeeded;
}
