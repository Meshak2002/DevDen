// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayerLoc.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"

UBTTask_FindPlayerLoc::UBTTask_FindPlayerLoc()
{
	NodeName = "Find Player Location"; 
}

EBTNodeResult::Type UBTTask_FindPlayerLoc::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* playerChar = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)) )
	{
		auto playerLoc = playerChar->GetActorLocation();
		if (bAroundPlayer)
		{
			if (auto* navigationSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation navLocation;
				if (navigationSystem->GetRandomPointInNavigableRadius(playerLoc, playerAroundRadius,navLocation))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), navLocation);
					return EBTNodeResult::Succeeded;
				}
			}
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), playerLoc);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
