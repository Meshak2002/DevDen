// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordGrappleNotify.h"

void USwordGrappleNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	OnNotified.Broadcast();
	Super::Notify(MeshComp, Animation, EventReference);
}
