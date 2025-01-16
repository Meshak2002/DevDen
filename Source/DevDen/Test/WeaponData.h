// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponData.generated.h"

USTRUCT(BlueprintType)
struct FWeaponsData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float attackValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float defenseValue;
};

UCLASS(BlueprintType)
class DEVDEN_API UWeaponData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeaponsData straightSword;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeaponsData urumi;
};
