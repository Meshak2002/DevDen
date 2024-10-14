// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class DEVDEN_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public :
	explicit AEnemyAIController(FObjectInitializer const& ObjectInitializer);

	virtual void OnPossess(APawn* InPawn) override;

	class UAISenseConfig_Sight* aiSightConfig;

	void SetupPerception();

	UFUNCTION()
	void TargetDetected(AActor* Actor, FAIStimulus const Stimulus);

protected:
};
