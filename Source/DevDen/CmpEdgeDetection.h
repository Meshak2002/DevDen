// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ActorComponent.h"
#include "CmpEdgeDetection.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEVDEN_API UCmpEdgeDetection : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCmpEdgeDetection();
	UCameraComponent* camera;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float rayAngleThreshold;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	FVector tRay;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	FVector mRay;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	FVector bRay;
private:
	FVector CameraLocation;
	FRotator CameraRotation;
	FVector camRay;

	float mAngleDecrementer;
	float tAngleDecrementer;
	FVector edgePt;
	const int MAX_ITERATIONS = 50; 

	FHitResult RayHit;
	ECollisionChannel channel = ECC_WorldStatic;
	void CheckForEdge();
	void GetCameraTransform();
	bool IsBtraceCollided(FRotator cameraRot);
	void MidTraceDetectEdge(FRotator cameraRot);
	void TopTraceDetectEdge(FRotator cameraRot);
};
