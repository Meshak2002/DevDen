// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/Engine.h"  
#include "GameFramework/CharacterMovementComponent.h" 
#include "BP_Urumi_.h"
#include "HealthComponent.h"
#include "SwordComboNotify.h"
#include "SwordGrappleNotify.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include <Perception/AISense_Sight.h>

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	cameraSpringArm->SetupAttachment(RootComponent);
	cameraSpringArm->TargetArmLength = 300.0f;
	
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(cameraSpringArm);
	 
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	SetupStimulusSource();
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (eneDetectCollider)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Fixed");
		eneDetectCollider->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnColOverlapBegin);
		eneDetectCollider->OnComponentEndOverlap.AddDynamic(this, &AMyCharacter::OnColOverlapEnd);
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "NOPE");
	}
	SetupNotify(AttackAnimMontage);
	SetupNotify(hAttackAnimMontage);

}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForw);
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::Strafe);
	PlayerInputComponent->BindAxis("MouseX", this, &AMyCharacter::MouseSide);
	PlayerInputComponent->BindAxis("MouseY", this, &AMyCharacter::MouseUpp);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMyCharacter::StartAttack);
	PlayerInputComponent->BindAction("Hattack", IE_Pressed, this, &AMyCharacter::HeavyAttack);
	PlayerInputComponent->BindAction("Hattack", IE_Released, this, &AMyCharacter::ReleaseHook);
}
void AMyCharacter::MoveForw(float inputValue)
{
	AddMovementInput(camera->GetForwardVector(), inputValue);
}
void AMyCharacter::Strafe(float inputValue)
{
	AddMovementInput(camera->GetRightVector(), inputValue);
}
void AMyCharacter::MouseSide(float inputValue)
{
	AddControllerYawInput(inputValue);
}
void AMyCharacter::MouseUpp(float inputValue)
{
	AddControllerPitchInput(inputValue);
}

void AMyCharacter::OnColOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || (OtherActor == this)) // Check if the other actor is valid and not self
	{
		return;
	}
	if (!enemiesInRange.Contains(OtherActor) && OtherActor->FindComponentByClass<UHealthComponent>())
		enemiesInRange.Add(OtherActor);
}
void AMyCharacter::OnColOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor || (OtherActor == this)) // Check if the other actor is valid and not self
	{
		return;
	}
	if (enemiesInRange.Contains(OtherActor))
		enemiesInRange.Remove(OtherActor);
}

void AMyCharacter::SetupNotify(UAnimMontage* animMontage)
{
	if (!animMontage)
		return;

	const auto notifyEvents = animMontage->Notifies;
	for (FAnimNotifyEvent eventNotify : notifyEvents)
	{
		if (const auto swordComboNotify = Cast<USwordComboNotify>(eventNotify.Notify))
		{
			swordComboNotify->OnNotified.AddUObject(this, &AMyCharacter::OnComboNotified);
		}
		else if (const auto grappleNotify = Cast<USwordGrappleNotify>(eventNotify.Notify))
		{
			grappleNotify->OnNotified.AddUObject(this, &AMyCharacter::OnGrappleNotified);
		}
	}
}

void AMyCharacter::OnComboNotified()
{
	attackIndex--;
	for (UHealthComponent* enemyHealth : actorsHealth)
	{
		if(enemyHealth)
			enemyHealth->Recover(actorsHealth);
		else
			actorsHealth.Remove(enemyHealth);
	}
	if (attackIndex < 0)
	{
		StopAnimMontage(AttackAnimMontage);
	}
}

void AMyCharacter::OnGrappleNotified()
{
	if (enemiesInRange.Num() <= 0 || hookDetected || !enemiesInRange[0])
		return;
	grabbedActor = enemiesInRange[0];
	impactPos = grabbedActor->GetActorLocation();
	GetCharacterMovement()->DisableMovement();
	GetMesh()->GetAnimInstance()->Montage_Pause(hAttackAnimMontage);
	if (USkeletalMeshComponent* eneSkel = grabbedActor->FindComponentByClass<USkeletalMeshComponent>())
	{
		weapon->Hook(impactPos, grabbedActor, FName("Mesh"), FName("Neck"));
	}
	else
	{
		weapon->Hook(impactPos);
	}
	GetWorldTimerManager().SetTimer(DistanceCheckTimerHandle, this, &AMyCharacter::DelayOnHook, 1.0f, false);
}

void AMyCharacter::DelayOnHook()
{
	hookDetected = true;
	if(!rtClickPress)
		ReleaseHook();
}

void AMyCharacter::ReleaseHook()
{
	rtClickPress = false;
	if (hookDetected && grabbedActor)
	{
		GetMesh()->GetAnimInstance()->Montage_Resume(hAttackAnimMontage);
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		weapon->UnHook();
		UHealthComponent* eneHealth = grabbedActor->FindComponentByClass<UHealthComponent>();
		if (!eneHealth) return;
		eneHealth->Recover(actorsHealth);
		eneHealth->Damage(1,this, actorsHealth,FVector::Zero(),EDamageType::Grapple);
		hookDetected = false;
	}
}

AActor* AMyCharacter::closerTarget()
{
	return nullptr;
}

void AMyCharacter::SetupStimulusSource()
{
	if (!stimulus)
		return;
	stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>()); 
	stimulus->RegisterWithPerceptionSystem();
}

void AMyCharacter::StartAttack()
{
	if (!AttackAnimMontage)
		return;
	if (!GetMesh()->GetAnimInstance())
		return;

	bool isMontagPlaying = GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackAnimMontage);
	if (!isMontagPlaying)
	{
		attackIndex = 0;
		PlayAnimMontage(AttackAnimMontage);
		FOnMontageEnded OnMontageEndedDelegate;
		OnMontageEndedDelegate.BindUObject(this, &AMyCharacter::OnAttackMontageEnded);
		GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(OnMontageEndedDelegate, AttackAnimMontage);
	}
	else
	{
		attackIndex = 1;
	}
}

void AMyCharacter::HeavyAttack()
{
	rtClickPress = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Pressed");
	if (!hAttackAnimMontage || !GetMesh()->GetAnimInstance())
		return;
	bool isMontagPlaying = GetMesh()->GetAnimInstance()->Montage_IsActive(hAttackAnimMontage);
	if (!isMontagPlaying)
	{
		PlayAnimMontage(hAttackAnimMontage);
		FOnMontageEnded OnMontageEndedDelegate;
		OnMontageEndedDelegate.BindUObject(this, &AMyCharacter::OnAttackMontageEnded);
		GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(OnMontageEndedDelegate, hAttackAnimMontage);
	}
	
}

void AMyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == AttackAnimMontage)
	{
		attackIndex = 0;
	}
	if (Montage == hAttackAnimMontage)
	{
		hookDetected = false;
	}
}
void AMyCharacter::LineTrace()
{
	if (!weapon->urumiWeapon)
		return;
	USkeletalMeshComponent* mesh = weapon->urumiWeapon;
	FCollisionQueryParams TraceParams;
	weapon->urumiWeapon->SetCollisionProfileName("NoCollision");
	TraceParams.AddIgnoredActor(this);
	TraceParams.AddIgnoredActor(weapon);

	for (int i = 1; i <= 13; i++)
	{
		FString SocketNameStart = FString::Printf(TEXT("s%d"), i);
		FString SocketNameEnd = FString::Printf(TEXT("s%d"), i + 1);
		FVector StartLocation = mesh->GetSocketLocation(FName(*SocketNameStart));
		FVector EndLocation = mesh->GetSocketLocation(FName(*SocketNameEnd));
		GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_WorldDynamic, TraceParams);
		//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 1, 0, 1); //Debug lines
		if (HitResult.bBlockingHit)
		{
			UHealthComponent* healthComp = HitResult.GetActor()->FindComponentByClass<UHealthComponent>();
			if (!healthComp)
				return;
			if (!actorsHealth.Contains(healthComp))
				actorsHealth.Add(healthComp);
			healthComp->Damage(damagePower,this,actorsHealth,HitResult.ImpactPoint);
		}
	}
	MakeFreeFlowCombat();
}

void AMyCharacter::MakeFreeFlowCombat()
{
	FRotator ControlRotation = GetControlRotation();
	FRotator NewRotation(0.0f, ControlRotation.Yaw, 0.0f);  // Keep only the yaw

	// Smoothly update rotation
	FRotator InterpolatedRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, GetWorld()->DeltaTimeSeconds, 5.0f);
	SetActorRotation(InterpolatedRotation);
}

void AMyCharacter::SwitchToSwordCol()
{
	weapon->urumiWeapon->SetCollisionProfileName("Sword");
}

