// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnims.h"

// Sets default values for this component's properties
UEnemyAnims::UEnemyAnims()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyAnims::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEnemyAnims::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEnemyAnims::PlayAnim(UAnimMontage* anim)
{
	if (skeletalMeshComp && anim)
		skeletalMeshComp->GetAnimInstance()->Montage_Play(anim);
	else
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "No anim or skel or animInst");
}

