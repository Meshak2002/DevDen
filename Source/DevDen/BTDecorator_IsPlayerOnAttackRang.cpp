// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsPlayerOnAttackRang.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTDecorator_IsPlayerOnAttackRang::UBTDecorator_IsPlayerOnAttackRang()
{
	NodeName = "IsPlayerOnAttackRange";
}


bool UBTDecorator_IsPlayerOnAttackRang::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,uint8* NodeMemory) const
{
	if(auto* const ai = OwnerComp.GetAIOwner())
	{
		if(auto* const enemy=ai->GetPawn())
		{
			if(auto* const player = UGameplayStatics::GetPlayerPawn(GetWorld(),0))
			{
				float distanceBtw = enemy->GetDistanceTo(player);
				
				if(distanceBtw < attackRange)
					return true;
			}
		}
	}
	return false;
}
