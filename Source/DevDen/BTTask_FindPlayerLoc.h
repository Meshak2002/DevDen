// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindPlayerLoc.generated.h"

/**
 * 
 */
UCLASS()
class DEVDEN_API UBTTask_FindPlayerLoc : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_FindPlayerLoc();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bAroundPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float playerAroundRadius;
	
};
