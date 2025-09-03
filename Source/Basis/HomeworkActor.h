// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HomeworkActor.generated.h"

UCLASS()
class BASIS_API AHomeworkActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHomeworkActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* SM;

private:
	FTimerHandle MovingLogicTimerHandler;
	FVector InitLocation;

	float MovingInterval = 0.5f;
	int MovingCnt = 0;
	int EventCnt = 0;

private:
	void Move();
	int32 GetStep();

	void EventFunc();
};
