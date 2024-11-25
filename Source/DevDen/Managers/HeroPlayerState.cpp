// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroPlayerState.h"
#include "AbilitySystemComponent.h"

AHeroPlayerState::AHeroPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
}

UAbilitySystemComponent* AHeroPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
