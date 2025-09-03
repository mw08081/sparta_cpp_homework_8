// Fill out your copyright notice in the Description page of Project Settings.


#include "HomeworkActorSpawner.h"

#include "HomeworkActor.h"

// Sets default values
AHomeworkActorSpawner::AHomeworkActorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHomeworkActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->SpawnActor<AHomeworkActor>(HomeworkActorClass);
	UE_LOG(LogTemp, Warning, TEXT("Spawn Homework Actor"));
}
