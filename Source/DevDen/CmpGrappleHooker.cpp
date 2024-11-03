// Fill out your copyright notice in the Description page of Project Settings.


#include "CmpGrappleHooker.h"

#include "BP_Urumi_.h"
#include "GrapplePoint.h"
#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCmpGrappleHooker::UCmpGrappleHooker() :
	traceRadius(100) ,
	lerpSpeed(1),
	grndAnimPlaySpeed(1.75f),
	airdAnimPlaySpeed(1.4f),
	fallSpeed(3)
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCmpGrappleHooker::BeginPlay()
{
	Super::BeginPlay();
	player = Cast<AMyCharacter>(GetOwner());
	camera = player->camera;
	animInstance = player->GetMesh()->GetAnimInstance();
	onAnimEnded.BindUObject(this, &UCmpGrappleHooker::BeNormal);
}

void UCmpGrappleHooker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(grapplerState==EGrappleHookState::Searching)
		CheckForGrapplePts();
	if(grapplerState==EGrappleHookState::InMotion)
	{
		FVector nextPos = FMath::Lerp(GetOwner()->GetActorLocation(),acceptablePoint->landerPoint->GetComponentLocation(),lerpSpeed*DeltaTime);
		GetOwner()->SetActorLocation(nextPos);
		float distance = UE::Geometry::Distance(GetOwner()->GetActorLocation(),acceptablePoint->landerPoint->GetComponentLocation());
		//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,FString::Printf(TEXT("Dist : %f"),distance));
		if(distance<50)
		{
			grapplerState=EGrappleHookState::LandDetected;
			player->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			if(bPlayingOnAir)
				animInstance->Montage_Resume(airGrappleMontage);
			else
				animInstance->Montage_Resume(grndGrappleMontage);
		}
	}
	if(grapplerState==EGrappleHookState::FallDown)
	{
		FVector velocity = player->GetCharacterMovement()->Velocity;
		//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green,FString::Printf(TEXT("Vel : %f"),velocity.Z));

		if(velocity.Z < -10.0f)
			bPlayerFalling = true;
		else
		{
			bPlayerFalling = false;
			 Land();
		}
	}
}

void UCmpGrappleHooker::CheckForGrapplePts()
{
	TArray<FHitResult> hits;
	TArray<AGrapplePoint*> grapplePoints;
	FCollisionObjectQueryParams params;
	params.AddObjectTypesToQuery(ECC_GameTraceChannel2);
	
	GetWorld()->SweepMultiByObjectType(hits,GetOwner()->GetActorLocation(),GetOwner()->GetActorLocation(),
		FQuat::Identity,params,FCollisionShape::MakeSphere(traceRadius));
	//DrawDebugSphere(GetWorld(), GetOwner()->GetActorLocation(), 1000.0f, 12, FColor::White);
	for (auto Hit : hits)
	{
		if(AGrapplePoint* grabPoint = Cast<AGrapplePoint>(Hit.GetActor()))
		{
			if(!grapplePoints.Contains(grabPoint))
				grapplePoints.Add(grabPoint);
		}
	}
	if(grapplePoints.Num()<=0)
		acceptablePoint = nullptr;
	else
		GetAcceptablePoint(grapplePoints);
}

 void UCmpGrappleHooker::GetAcceptablePoint(TArray<class AGrapplePoint*> GrapplePoints)
{
	if(!camera)
		return;
	float closerAnglePt=0;
	for(auto grapplePoint : GrapplePoints)
	{
		grapplePoint->Disable();
		FVector playerTargetDir = grapplePoint->GetActorLocation() - camera->GetComponentLocation();
		playerTargetDir.Normalize();
		float dotValue = camera->GetForwardVector().Dot(playerTargetDir);
		if(FMath::Abs(dotValue) >= closerAnglePt)
		{
			closerAnglePt = dotValue;
			acceptablePoint = grapplePoint;
			acceptablePoint->Enable();
		//	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,FString::Printf(TEXT("Dot %f"),dotValue));
		}
	}
}

void UCmpGrappleHooker::TriggerGrappleHook()
{
	if(!acceptablePoint || !grndGrappleMontage || !airGrappleMontage)
		return;
	if(player->GetCharacterMovement()->Velocity.Z !=0)
	{
	//	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,FString::Printf(TEXT("Airrrrr___________________________________________Vel : %f"),player->GetCharacterMovement()->Velocity.Z));
		animInstance->Montage_Play(airGrappleMontage,airdAnimPlaySpeed);
		animInstance->Montage_SetEndDelegate(onAnimEnded,airGrappleMontage);
		bPlayingOnAir=true;
	}
	else
	{
	//	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,FString::Printf(TEXT("Down________________________________________________________Vel : %f"),player->GetCharacterMovement()->Velocity.Z));
		animInstance->Montage_Play(grndGrappleMontage,grndAnimPlaySpeed);
		animInstance->Montage_SetEndDelegate(onAnimEnded,grndGrappleMontage);
		bPlayingOnAir=false;
	}
	
	FVector playerTargetDir = acceptablePoint->GetActorLocation() - player->GetActorLocation();
	playerTargetDir.Normalize();
	FRotator targetRotator=playerTargetDir.Rotation();
	targetRotator.Pitch=	player->GetActorRotation().Pitch;
	targetRotator.Roll =	player->GetActorRotation().Roll;
	player->SetActorRotation(targetRotator);
	
	player->SwitchHands(FName("hand_lSocket"));
	player->GetCharacterMovement()->DisableMovement();

}

void UCmpGrappleHooker::MakeAHook()	///Notify Call
{
	player->weapon->Hook(acceptablePoint->Sphere->GetComponentLocation());
}

void UCmpGrappleHooker::StartFly()	///Notify Call
{
	grapplerState = EGrappleHookState::InMotion;
}

void UCmpGrappleHooker::ReleaseHook()	///Notify Call
{
	if(grapplerState!=EGrappleHookState::InMotion)
		return;
//	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,"	ReleaseHook");
	player->weapon->UnHook();
	if(bPlayingOnAir)
		animInstance->Montage_Pause(airGrappleMontage);
	else
		animInstance->Montage_Pause(grndGrappleMontage);
}

void UCmpGrappleHooker::PauseFall()
{
	if(bPlayingOnAir)
		animInstance->Montage_Pause(airGrappleMontage);
	else
		animInstance->Montage_Pause(grndGrappleMontage);
	grapplerState = EGrappleHookState::FallDown;
//	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,"	Pause Fall");

	player->GetCharacterMovement()->GravityScale = fallSpeed;	
}

void UCmpGrappleHooker::Land()		
{
//	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,"	Land");
	player->weapon->UnHook();
	if(bPlayingOnAir)
		animInstance->Montage_Resume(airGrappleMontage);
	else
		animInstance->Montage_Resume(grndGrappleMontage);
	grapplerState=EGrappleHookState::Searching;
	player->GetCharacterMovement()->GravityScale = 1;	
}

void UCmpGrappleHooker::BeNormal(UAnimMontage* anim , bool interrupted)
{
	//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,"Normallllllllllll");
}




