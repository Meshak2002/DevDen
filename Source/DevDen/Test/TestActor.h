// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "TestInterface.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

UCLASS()
class DEVDEN_API ATestActor : public AActor , public ITestInterface
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestDelegate);
public:
	ATestActor();
	UPROPERTY(BlueprintAssignable)
	FTestDelegate testDelegate;

	UFUNCTION(BlueprintCallable)
	void DelegateCall();

	UFUNCTION(BlueprintCallable)
	virtual void overhorse();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	void Tester() override;

	void BpTester_Implementation() override;
};
