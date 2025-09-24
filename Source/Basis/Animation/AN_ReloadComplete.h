// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_ReloadComplete.generated.h"

/**
 * 
 */
UCLASS()
class BASIS_API UAN_ReloadComplete : public UAnimNotify
{
	GENERATED_BODY()

public: 
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
