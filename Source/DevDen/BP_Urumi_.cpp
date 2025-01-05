// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Urumi_.h"
#include "Engine/Engine.h"  
#include "CableComponent.h"
#include "CableEndTarget.h"
#include "AnimUrumi.h"

// Sets default values
ABP_Urumi_::ABP_Urumi_()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	aPt->SetupAttachment(RootComponent);
	bPt->SetupAttachment(RootComponent);
	tPt->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABP_Urumi_::BeginPlay()
{
	Super::BeginPlay();
	cableEndTarget=GetWorld()->SpawnActor<ACableEndTarget>();
	cableEndTargetScene = Cast<USceneComponent>(cableEndTarget->GetRootComponent());
	TurnOnSkeletel();

}

// Called every frame
void ABP_Urumi_::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABP_Urumi_::TurnOnSkeletel()
{
	if (!urumiWeapon || !cableComponent)
		return;
	urumiWeapon->SetVisibility(true);
	cableComponent->SetVisibility(false);
	cableComponent->bAttachEnd = false;
}

void ABP_Urumi_::TurnOnCable()
{
	if (!urumiWeapon || !cableComponent)
		return;
	urumiWeapon->SetVisibility(false);
	cableComponent->SetVisibility(true);
}

void ABP_Urumi_::SetCableEndPos(AActor* targetActor, FName compName, FName sockName)
{
	cableComponent->bAttachEnd = true;
	cableComponent->SetAttachEndTo(targetActor, compName, sockName);
}

void ABP_Urumi_::SetCableEndPos(FVector pos)
{
	cableComponent->bAttachEnd = true;
	cableEndTargetScene->SetWorldLocation(pos);
	cableComponent->SetAttachEndTo(cableEndTarget, NAME_None);
}

void ABP_Urumi_::Hook(FVector impactPos, AActor* attachActor, FName compName, FName boneName)
{
	urumiWeapon->SetCollisionProfileName("NoCollision");
	TurnOnCable();
	if (attachActor != nullptr)
		SetCableEndPos(attachActor, compName, boneName);
	else
		SetCableEndPos(impactPos);
	UAnimUrumi* anim = Cast<UAnimUrumi>(urumiWeapon->GetAnimInstance());
	if (anim)
	{
		anim->turnIK = true;
		anim->ikGoalPos = impactPos;
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("NOAnim")));
}


void ABP_Urumi_::UnHook()
{
	TurnOnSkeletel();
	urumiWeapon->SetCollisionProfileName("Sword");
	UAnimUrumi* anim = Cast<UAnimUrumi>(urumiWeapon->GetAnimInstance());
	if (!anim)
		return;
	anim->turnIK = false;
}




