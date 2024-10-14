#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyAnims.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHealthComponent::Recover()
{
	isAttacked = false;
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
	actorsHealth.Remove(this);
	GetOwner()->Destroy();
}

void UHealthComponent::Damage(int Damage, TArray<UHealthComponent*>& actorsHealth, EDamageType damageType)
{
	if (isAttacked)
		return;
	Health -= Damage;
	isAttacked = true;
	if (damageType == EDamageType::Grapple)
		GrappleDamage();
	if (Health <= 0)
		Die(actorsHealth);
	
}


