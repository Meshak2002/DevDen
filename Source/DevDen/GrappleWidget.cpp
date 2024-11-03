// Fill out your copyright notice in the Description page of Project Settings.


#include "GrappleWidget.h"

void UGrappleWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(progressBar)
		SetAcceptableAngle(1);
}

void UGrappleWidget::SetAcceptableAngle(float value)
{
	progressBar->SetPercent(value);
}
