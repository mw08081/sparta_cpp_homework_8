// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrainingDummy.generated.h"

UCLASS()
class BASIS_API ATrainingDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrainingDummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

private:
	UPROPERTY(EditAnywhere)
	FVector MovingDirection;
	UPROPERTY(EditAnywhere)
	float MovingDistance;
	UPROPERTY(EditAnywhere)
	float MovingSpeed;

	bool IsMoveToTarget = true;
	float CurMovingDist = 0;
	FVector OrgLocation;
	FVector TargetLocation;

};
