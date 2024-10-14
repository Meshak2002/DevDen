// Fill out your copyright notice in the Description page of Project Settings.


#include "CableEndTarget.h"

// Sets default values
ACableEndTarget::ACableEndTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = DefaultSceneRoot;
}

// Called when the game starts or when spawned
void ACableEndTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACableEndTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

