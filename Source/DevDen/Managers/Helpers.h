// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Helpers.generated.h"

/**
 * 
 */
UCLASS()
class DEVDEN_API UHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/** A simple global function to normalize a value */
	UFUNCTION(BlueprintCallable, Category = "Helper")
	static bool IsRotatingCounterClockwise(const FVector2D& CurrentStickInput, const FVector2D& PreviousStickInput, float DeadZone = 0.2f);

	
};
