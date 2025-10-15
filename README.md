# 과제 8번

과제 외 구현한 항목
- AI(BT, BTTask, BTService)
- Task
```c++
// Patroll
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

// Attack
EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& BTC, uint8* NodeMemory)
{
	UBlackboardComponent* BBC = BTC.GetBlackboardComponent();
	if (BBC == nullptr) return EBTNodeResult::Failed;

	// AI 검증
	AAIController* AIController = BTC.GetAIOwner();
	if (AIController == nullptr) return EBTNodeResult::Failed;

	//ACharacterBase* AIPawn = Cast<ACharacterBase>(BTC.GetOwner()); // 도 가능
	AAIBase* AICharacter = static_cast<AAIBase*>(AIController->GetPawn());
	if(AICharacter == nullptr) return EBTNodeResult::Failed;

	// Target Player 검증
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController == nullptr) return EBTNodeResult::Failed;

	APlayerBase* TargetPawn = static_cast<APlayerBase*>(PlayerController->GetPawn());
	if (TargetPawn == nullptr) return EBTNodeResult::Failed;
	 
	// 공격위치 설정
	AIController->StopMovement();

	AICharacter->Attack();

	return EBTNodeResult::Succeeded;
}
```
- Servcie
```c++
// Find Target
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

// Aim
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
```
- Hit By Bone(Head;Spine;Other)
```c++
ACharacterBase* Target = Cast<ACharacterBase>(OtherActor);
if (IsValid(Target)) {
	float Damage = WeaponOwner->Strength;

	if (Hit.BoneName.ToString().StartsWith("Head")) {
		Damage *= 1.2f;
		DrawDebugSphere(GetWorld(), Hit.Location, 1.5f, 24, FColor::Red, false, 3);
	}
	else if (Hit.BoneName.ToString().StartsWith("Spine")) {
		Damage *= 0.7f;
		DrawDebugSphere(GetWorld(), Hit.Location, 1.5f, 24, FColor::Yellow, false, 3);
	}
	else {
		Damage *= 0.4f;
	}
	Target->Hit((int)Damage, WeaponOwner);
}
```
- widget(C++)

----
과제 시연 영상
- 시작 UI와 ai  
![ai startUI](https://github.com/user-attachments/assets/bde219b4-914e-4012-9015-5cdcfeb693d4)

- 전투 장면(UI 업데이트)  
![B1](https://github.com/user-attachments/assets/ba1bebf3-911c-472f-88c6-f9eb069443ef)

- 전투 장면(체력감소)  
![B2](https://github.com/user-attachments/assets/9259f2f3-ad46-44dd-8d45-1808f54f1e3d)

- 전투 장면(체력 완전 회복- 부스트)  
![B3](https://github.com/user-attachments/assets/1f531585-cce5-4eba-a19b-84143a4ea689)
 
- 스테이지 클리어(UE_LOG)  
![stageClear](https://github.com/user-attachments/assets/eb474afd-a05a-45fa-92d8-294f372e3f05)

- Restart UI  
![restart](https://github.com/user-attachments/assets/f9e1bd06-4da2-4d9e-9198-068c30af038c)


  
