// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class DEVDEN_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* cameraSpringArm;

	void MoveForw(float inputValue);

	void Strafe(float inputValue);

	void MouseUpp(float inputValue);

	void MouseSide(float inputValue);

	UPROPERTY(EditAnywhere)
	int damagePower;

	UPROPERTY(VisibleAnywhere)
	int attackIndex;
	
	void SetupNotify(UAnimMontage* animMontage);

	void OnComboNotified();

	void OnGrappleNotified();

	void StartAttack();

	void HeavyAttack();

	void ReleaseHook();

	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	

	bool hookDetected;

	FHitResult HitResult;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class UAnimMontage* AttackAnimMontage ;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class UAnimMontage* hAttackAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* ImpactPointComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void LineTrace();

	UFUNCTION(BlueprintCallable)
	void SwitchToSwordCol();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ABP_Urumi_* weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* eneDetectCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> enemiesInRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UHealthComponent*> actorsHealth;

	class UAIPerceptionStimuliSourceComponent* stimulus;

	void SetupStimulusSource();


private : 
	FTimerHandle DistanceCheckTimerHandle;

	void DelayOnHook();

	AActor* closerTarget();

	AActor* grabbedActor;

	FVector impactPos;

	bool rtClickPress;

	UFUNCTION()
	void OnColOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnColOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
