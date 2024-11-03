// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CmpGrappleHooker.generated.h"

UENUM(BlueprintType)
enum class EGrappleHookState : uint8
{
	Searching,
	InMotion,
	LandDetected,
	FallDown
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEVDEN_API UCmpGrappleHooker : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCmpGrappleHooker();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float traceRadius;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAnimMontage* grndGrappleMontage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float grndAnimPlaySpeed;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAnimMontage* airGrappleMontage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float airdAnimPlaySpeed;
	
	bool bPlayingOnAir;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UCameraComponent* camera;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float lerpSpeed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EGrappleHookState grapplerState=EGrappleHookState::Searching;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AGrapplePoint* acceptablePoint;

	void CheckForGrapplePts();
	
	UFUNCTION(BlueprintCallable)
	void MakeAHook();

	UFUNCTION(BlueprintCallable)
	void StartFly();
	
	UFUNCTION(BlueprintCallable)
	void ReleaseHook();

	bool bPlayerFalling;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float fallSpeed;
	
	UFUNCTION(BlueprintCallable)
	void PauseFall();
	
	UFUNCTION(BlueprintCallable)
	void Land();
	
	UFUNCTION(BlueprintCallable)
	void TriggerGrappleHook();			//Button Call
	
private:

	class AMyCharacter* player;

	UAnimInstance* animInstance;

	void GetAcceptablePoint(TArray<class AGrapplePoint*> GrapplePoints);

	UFUNCTION()
	void BeNormal(UAnimMontage* anim , bool interrupted);

	FOnMontageEnded onAnimEnded;
};
