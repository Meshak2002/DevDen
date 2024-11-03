// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "GrapplePoint.generated.h"

UCLASS()
class DEVDEN_API AGrapplePoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrapplePoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Enable();

	void Disable();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float sphereRotSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Sphere;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* scene;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* staticTree;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* landerPoint;
private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UWidgetComponent* Widget;

	
};
