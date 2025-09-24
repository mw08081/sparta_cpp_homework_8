// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrainingTarget.generated.h"

UCLASS()
class BASIS_API ATrainingTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrainingTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> ActorRoot;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

public:
	UFUNCTION()
	void OnHit(class UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void ExecRot();

private:
	UPROPERTY(EditAnywhere)
	bool IsAutoReturn = false;
	FTimerHandle AutoReturnHandle;

	bool IsPositiveSide = true;
	bool IsShouldRot = false;

	UPROPERTY(EditAnywhere)
	FRotator RotDirection;

	UPROPERTY(EditAnywhere)
	float RotSpeed = 90;

	FRotator OrgRot;

	UPROPERTY(EditAnywhere)
	float MaxRotAmmount = 90;
	float CurRotAmmount = 0;
};
