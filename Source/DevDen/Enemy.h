// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Enemy.generated.h"

UCLASS()
class DEVDEN_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBehaviorTree* behaviorTree;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	UBehaviorTree* GetBahaviorTree();

	void PlayAttackAnim();

private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* attackAnim;

	UPROPERTY()
	UAnimInstance* animInstance;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* boxCollider;

	UFUNCTION() 
	void OnAttackOverlapBegin(
	UPrimitiveComponent* const OverlappedComponent,
	AActor* const OtherActor,
	UPrimitiveComponent* const OtherComponent,
	int const OtherBodyIndex,
	bool const FromSweep,
	FHitResult const& SweepResult);
	
	UFUNCTION() 
	void OnAttackOverlapEnd(
	UPrimitiveComponent* const OverlappedComponent,
	AActor* const OtherActor,
	UPrimitiveComponent* OtherComponent,
	int const OtherBodyIndex);
};
