// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "HeroPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DEVDEN_API AHeroPlayerState : public APlayerState , public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AHeroPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAbilitySystemComponent* AbilitySystemComponent;
};