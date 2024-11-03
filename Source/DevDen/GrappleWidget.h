// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "GrappleWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEVDEN_API UGrappleWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	void SetAcceptableAngle(float value);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess=true	))
	UProgressBar* progressBar=nullptr;
	
};
