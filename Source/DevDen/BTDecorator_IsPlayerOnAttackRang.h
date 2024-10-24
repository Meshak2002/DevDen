// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_IsPlayerOnAttackRang.generated.h"

/**
 * 
 */
UCLASS()
class DEVDEN_API UBTDecorator_IsPlayerOnAttackRang : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTDecorator_IsPlayerOnAttackRang();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float attackRange;
};
