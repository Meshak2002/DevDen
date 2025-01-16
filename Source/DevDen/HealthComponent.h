// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NiagaraComponent.h"
#include "HealthComponent.generated.h"

UENUM()
enum class EDamageType : uint8
{
	NONE,
	Grapple
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEVDEN_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* bloodSound;
	
	UFUNCTION(BlueprintCallable)
	void Die();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Health;
	bool isAttacked;

	void GrappleDamage();

public:
	void Damage(int Damage, AActor* damager , TArray<UHealthComponent*>& actorsHealth,FVector damagePoint=FVector::Zero(), EDamageType damageType=EDamageType::NONE);
	void Recover(TArray<UHealthComponent*>& actorsHealth);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UEnemyAnims* enemyAnim;

	UPROPERTY(EditAnywhere)
	UParticleSystem* impactGrappleFX;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UNiagaraSystem* bloodFx;
	
	
private :
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* hitAnim;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* dieAnim;

	UPROPERTY()
	USkeletalMeshComponent* skeletalMesh;
};

