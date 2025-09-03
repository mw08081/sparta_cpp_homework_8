// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HomeworkActorSpawner.generated.h"

UCLASS()
class BASIS_API AHomeworkActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHomeworkActorSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AHomeworkActor> HomeworkActorClass;

	class AHomeworkActor* HomeworkActor;
};
