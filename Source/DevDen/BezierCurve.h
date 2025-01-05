// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BezierCurve.generated.h"

class UPoseableMeshComponent;

UCLASS()
class DEVDEN_API ABezierCurve : public AActor
{
	GENERATED_BODY()

public:
	ABezierCurve();
	
	void OnConstruction(const FTransform &Transform) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USkeletalMeshComponent* urumiWeapon;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UPoseableMeshComponent* urumiPoseable;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	 USceneComponent* aPt;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	 USceneComponent* bPt;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	 USceneComponent* tPt;

	UPROPERTY(EditAnywhere,BLueprintReadWrite)
	float alphaThreshold;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float substep;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float swordStepLength;
	void ResetCurve();
	

	
	UFUNCTION(BlueprintCallable)
	void TriggerBezier();
	void Drawer();
	void DrawCurve();
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefaultSceneRoot;
	FVector a;
	FVector b;
	FVector t;
	UPROPERTY(VisibleAnywhere)
	FVector a0;
	UPROPERTY(VisibleAnywhere)
	FVector a1;
	UPROPERTY(VisibleAnywhere)
	FVector alerp;
	UPROPERTY(VisibleAnywhere)
	FVector b0;
	UPROPERTY(VisibleAnywhere)
	FVector b1;
	UPROPERTY(VisibleAnywhere)
	FVector blerp;
	UPROPERTY(VisibleAnywhere)
	float alpha;
	UPROPERTY(VisibleAnywhere)
	float steps;
	UPROPERTY(VisibleAnywhere)
	FVector curvePt;
	UPROPERTY(VisibleAnywhere)
	TArray<FVector> curvePoints;
	UPROPERTY(VisibleAnywhere)
	TArray<FVector> swordSteps;
	UPROPERTY(VisibleAnywhere)
	FVector dummy;	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void Temp(USceneComponent* cmp, EUpdateTransformFlags UpdateTransformFlags, ETeleportType teleportType);
};
