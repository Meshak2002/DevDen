// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Enemy.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


AEnemyAIController::AEnemyAIController(FObjectInitializer const& ObjectInitializer)
{
	SetupPerception();
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (AEnemy* enemy = Cast<AEnemy>(InPawn))
	{
		if (UBehaviorTree* behaviorTree = enemy->GetBahaviorTree())
		{
			UBlackboardComponent* blackBoard;
			UseBlackboard(behaviorTree->BlackboardAsset, blackBoard);
			Blackboard = blackBoard;
			RunBehaviorTree(behaviorTree);
		}
	}
}

void AEnemyAIController::SetupPerception()
{
	aiSightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseSight_Config"));
	if (aiSightConfig)
	{
		UAIPerceptionComponent* perceptionCmp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception_Cmp"));
		SetPerceptionComponent(*perceptionCmp);
		aiSightConfig->SightRadius = 1000;
		aiSightConfig->LoseSightRadius = aiSightConfig->SightRadius + 25;
		aiSightConfig->PeripheralVisionAngleDegrees = 90;
		aiSightConfig->SetMaxAge(5.f);
		aiSightConfig->AutoSuccessRangeFromLastSeenLocation = 1100.f;
		aiSightConfig->DetectionByAffiliation.bDetectEnemies = true;
		aiSightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		aiSightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		//GetPerceptionComponent()->SetDominantSense(*aiSightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::TargetDetected);
		GetPerceptionComponent()->ConfigureSense(*aiSightConfig);
	}
}

void AEnemyAIController::TargetDetected(AActor* actor, FAIStimulus const stimulus)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "TargetDetected");
	if (auto* character = Cast<AMyCharacter>(actor))
	{
		GetBlackboardComponent()->SetValueAsBool("bPlayerDetected", stimulus.WasSuccessfullySensed());
	}
}

