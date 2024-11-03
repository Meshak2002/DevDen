// Fill out your copyright notice in the Description page of Project Settings.


#include "GrapplePoint.h"

// Sets default values
AGrapplePoint::AGrapplePoint() :
	Widget(CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent")) ) ,
	Sphere(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere")) ) ,
	landerPoint(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Landing Area"))),
	scene(CreateDefaultSubobject<USceneComponent>(TEXT("Root"))),
	staticTree(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticTree")))
{
	SetRootComponent(scene);
	staticTree->SetupAttachment(GetRootComponent());
	Sphere->SetupAttachment(staticTree);
	Widget->SetupAttachment(Sphere);
	landerPoint->SetupAttachment(staticTree);
	
	Widget->SetPivot(FVector2D(0.5f, 0.5f));
	Widget->SetDrawSize(FVector2D(200, 100)); // Fixed size
	Widget->SetDrawAtDesiredSize(true);
	Widget->SetTickWhenOffscreen(false);
	
	// Prevent perspective scaling
	
	Widget->SetBlendMode(EWidgetBlendMode::Transparent);
	Widget->SetWindowFocusable(false);
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGrapplePoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGrapplePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator newRot = Sphere->GetComponentRotation();
	newRot.Yaw+=sphereRotSpeed*DeltaTime;
	Sphere->SetRelativeRotation(newRot);
	Disable();
}

void AGrapplePoint::Enable()
{
	if(!Sphere)
		return;
	Sphere->SetVisibility(true);
}

void AGrapplePoint::Disable()
{
	if(!Sphere)
		return;
	Sphere->SetVisibility(false);
}

