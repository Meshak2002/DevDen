// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TestInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UTestInterface : public UInterface
{
	GENERATED_BODY()
};
class DEVDEN_API ITestInterface
{
	GENERATED_BODY()
public:
	virtual void Tester()=0;
	
	UFUNCTION(BlueprintNativeEvent)
	void BpTester();

	int intemp=5;
};
