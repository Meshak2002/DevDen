// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_FindRandomLoc.h"
#include "EnemyAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTT_FindRandomLoc::UBTT_FindRandomLoc()
{
	NodeName = "Get Random Location";
}

EBTNodeResult::Type UBTT_FindRandomLoc::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const aiController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const enemy = Cast<APawn>(aiController->GetPawn()))
		{
			auto const pawnLoc = enemy->GetActorLocation();
			if(auto* const navigation = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
			  FNavLocation navLoc;
			  
			  if (navigation->GetRandomPointInNavigableRadius(pawnLoc, searchableRadius, navLoc))
			  {
				  OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), navLoc.Location);
			  }
			  //FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			  return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
