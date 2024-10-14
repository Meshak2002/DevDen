// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_Urumi_.generated.h"

UCLASS()
class DEVDEN_API ABP_Urumi_ : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABP_Urumi_();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCableComponent* cableComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* urumiWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* cableEndTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* cableEndTargetScene;

	void TurnOnSkeletel();
	void TurnOnCable();
	void SetCableEndPos(AActor* targetActor, FName compName = NAME_None, FName sockName= NAME_None);
	void SetCableEndPos(FVector pos);
	void Hook(FVector impactPos,AActor* attachActor=nullptr, FName compName= FName(""), FName boneName=FName(""));
	void UnHook();
};
