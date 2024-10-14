// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CableEndTarget.generated.h"

UCLASS()
class DEVDEN_API ACableEndTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACableEndTarget();
	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefaultSceneRoot;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
