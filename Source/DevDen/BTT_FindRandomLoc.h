// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_FindRandomLoc.generated.h"

/**
 * 
 */
UCLASS()
class DEVDEN_API UBTT_FindRandomLoc : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public : 
	 UBTT_FindRandomLoc();

	 virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	 UPROPERTY(EditAnywhere , BlueprintReadWrite)
	 float searchableRadius;
};
