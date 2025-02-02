// Fill out your copyright notice in the Description page of Project Settings.


#include "Helpers.h"

bool UHelpers::IsRotatingCounterClockwise(const FVector2D& CurrentStickInput, const FVector2D& PreviousStickInput, float DeadZone)
{
	if(CurrentStickInput.Size() < DeadZone || PreviousStickInput.Size() < DeadZone)
		return false;
	float zCrossProduct = PreviousStickInput.X * CurrentStickInput.Y - PreviousStickInput.Y * CurrentStickInput.X;
	return zCrossProduct > 0;
}
