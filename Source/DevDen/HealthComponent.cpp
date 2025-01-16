#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyAnims.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Enemy.h"

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

void UHealthComponent::Die()
{
	//Trash
	//skeletalMesh->GetAnimInstance()->Montage_Pause(dieAnim);
}

void UHealthComponent::Damage(int Damage, AActor* damager, TArray<UHealthComponent*>& actorsHealth,FVector damagePoint, EDamageType damageType)
{
	
	if (isAttacked)
		return;

	Health -= Damage;
	if(damagePoint!=FVector::Zero() && bloodFx)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),bloodFx,damagePoint,FRotator::ZeroRotator,FVector(1.0f),true);
		//DrawDebugSphere(GetWorld(),damagePoint,20,20,FColor::Red);
		if(bloodSound)
			UGameplayStatics::PlaySoundAtLocation(GetWorld(),bloodSound,damagePoint);
	}
	
	if (Health <= 0)
	{
		if(actorsHealth.Contains(this))
			actorsHealth.Remove(this);
		if(!dieAnim)
			return;
		AEnemy* enemy=Cast<AEnemy>(GetOwner());
		if(enemy)
		{
			enemy->GetController()->Destroy();
			//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Cyan,"EnemyAI");
		}
		skeletalMesh->GetAnimInstance()->Montage_Play(dieAnim,1.5f);
		DestroyComponent();
		return;
	}
	
	isAttacked = true;
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(),damager->GetActorLocation());
	GetOwner()->SetActorRotation(targetRotation);
	if(hitAnim && (skeletalMesh && hitAnim))
		skeletalMesh->GetAnimInstance()->Montage_Play(hitAnim,1.5f);
	if (damageType == EDamageType::Grapple)
		GrappleDamage();
} 


