// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAbility1.h"

UCustomAbility1::UCustomAbility1()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UCustomAbility1::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                      const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (CommitAbility(Handle, ActorInfo, ActivationInfo)) // Apply costs or cooldowns
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0,FColor::Red,TEXT("Ability Activated!"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false); // End immediately
	}
}

void UCustomAbility1::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	GEngine->AddOnScreenDebugMessage(-1,5.0,FColor::Red,TEXT("Ability Ended"));
}

bool UCustomAbility1::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}
