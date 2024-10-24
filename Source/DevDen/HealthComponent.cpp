#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyAnims.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	skeletalMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
}

void UHealthComponent::Recover(TArray<UHealthComponent*>& actorsHealth)
{
	isAttacked = false;
	if(actorsHealth.Contains(this))
		actorsHealth.Remove(this);
}

void UHealthComponent::GrappleDamage()
{
	if (impactGrappleFX && enemyAnim->skeletalMeshComp)  // For humanoid NPC
	{
		UGameplayStatics::SpawnEmitterAttached(impactGrappleFX, enemyAnim->skeletalMeshComp, FName("Neck"));
		enemyAnim->PlayAnim(enemyAnim->hitOnGrapple);
	}
	else     // For Shapes and Objects
	{
		UPrimitiveComponent* phyComp = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
		if (!phyComp) return;
		phyComp->SetSimulatePhysics(true);
		FVector externalForce = FVector(500.0f, 0.0f, 100.0f);
		phyComp->AddImpulse(externalForce * phyComp->GetMass());
	}
}

void UHealthComponent::Die(TArray<UHealthComponent*>& actorsHealth)
{
	if(actorsHealth.Contains(this))
		actorsHealth.Remove(this);
	GetOwner()->Destroy();
}

void UHealthComponent::Damage(int Damage, AActor* damager, TArray<UHealthComponent*>& actorsHealth,FVector damagePoint, EDamageType damageType)
{
	
	if (isAttacked)
		return;
	Health -= Damage;
	isAttacked = true;
	
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(),damager->GetActorLocation());
	GetOwner()->SetActorRotation(targetRotation);
	if(hitAnim && (skeletalMesh && hitAnim))
		skeletalMesh->GetAnimInstance()->Montage_Play(hitAnim,1.5f);
	if (damageType == EDamageType::Grapple)
		GrappleDamage();
	if(damagePoint!=FVector::Zero() && bloodFx)
	{
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),bloodFx,damagePoint,FRotator::ZeroRotator,true);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),bloodFx,damagePoint,FRotator::ZeroRotator,FVector(1.0f),true);
		DrawDebugSphere(GetWorld(),damagePoint,20,20,FColor::Red);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,FString::Printf(TEXT("DamagePoint: %s"),*FString(damagePoint.ToString()) ));
	}
	if (Health <= 0)
		Die(actorsHealth); 
} 


