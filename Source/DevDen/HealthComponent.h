// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Health;
	bool isAttacked;

	void GrappleDamage();
	void Die(TArray<UHealthComponent*>& actorsHealth);

public:
	void Damage(int Damage, TArray<UHealthComponent*>& actorsHealth, EDamageType damageType=EDamageType::NONE);
	void Recover();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UEnemyAnims* enemyAnim;

	UPROPERTY(EditAnywhere)
	UParticleSystem* impactGrappleFX;
};

