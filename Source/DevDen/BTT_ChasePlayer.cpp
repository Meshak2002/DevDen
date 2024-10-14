// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_ChasePlayer.h"
#include "EnemyAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
UBTT_ChasePlayer::UBTT_ChasePlayer()
{
	NodeName = "ChaseTarget";
}

EBTNodeResult::Type UBTT_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* aiController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner()))
	{
		auto targetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(aiController, targetLocation);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
