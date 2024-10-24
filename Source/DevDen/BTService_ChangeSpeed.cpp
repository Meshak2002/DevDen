// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ChangeSpeed.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTService_ChangeSpeed::UBTService_ChangeSpeed()
{
	NodeName = "Change Speed To";
	bNotifyBecomeRelevant = true;
}

void UBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const ai = OwnerComp.GetAIOwner())
	{
		if (auto* const enemyCharac = ai->GetCharacter())
		{
			enemyCharac->GetCharacterMovement()->MaxWalkSpeed = speed;
		}
	}
}
