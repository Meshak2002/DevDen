// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimUrumi.generated.h"

/**
 * 
 */
UCLASS()
class DEVDEN_API UAnimUrumi : public UAnimInstance
{
	GENERATED_BODY()
	
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ikGoalPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool turnIK;
};
