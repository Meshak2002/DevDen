// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"

#include "Enemy.h"
#include "EnemyAIController.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = "Attack";
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const aiController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()))
	{
		if(auto* const enemy = Cast<AEnemy>( aiController->GetPawn()) )
		{
			enemy->PlayAttackAnim();
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
