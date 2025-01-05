
#include "BezierCurve.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/PoseableMeshComponent.h"

// Sets default values
ABezierCurve::ABezierCurve()
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	urumiWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("URUMI Sword"));
	urumiWeapon->SetupAttachment(RootComponent);
	urumiPoseable = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("URUMI Poseable"));
	urumiPoseable->SetupAttachment(RootComponent);
	
	aPt = CreateDefaultSubobject<USceneComponent>(TEXT("A Point"));
	aPt->SetRelativeLocation(FVector(0, 0, 0));  
	bPt = CreateDefaultSubobject<USceneComponent>(TEXT("B Point"));
	bPt->SetRelativeLocation(FVector(100, 0, 0));  
	tPt = CreateDefaultSubobject<USceneComponent>(TEXT("T Point"));
	tPt->SetRelativeLocation(FVector(50, 50, 0));  
}

void ABezierCurve::OnConstruction(const FTransform &Transform)
{
	Super::OnConstruction(Transform);
}


void ABezierCurve::ResetCurve()
{
	dummy=aPt->GetComponentLocation();
	steps=1/substep;
	a0 = aPt->GetComponentLocation();
	a1 = tPt->GetComponentLocation();
	b0 = tPt->GetComponentLocation();
	b1 = bPt->GetComponentLocation();
	alpha=0;
	curvePoints.Empty();
	swordSteps.Empty();
	TriggerBezier();
}

void ABezierCurve::TriggerBezier()
{
	while(alpha<alphaThreshold)
	{
		alerp = FMath::Lerp(a0,a1,alpha);
		blerp = FMath::Lerp(b0,b1,alpha);				
		curvePt = FMath::Lerp(alerp,blerp,alpha);	
		alpha+=steps;
		curvePoints.Add(curvePt);
	}
	DrawCurve();
}

void ABezierCurve::Drawer()
{
	DrawDebugSphere(GetWorld(),aPt->GetComponentLocation(),5,10,FColor::Red);
	DrawDebugSphere(GetWorld(),bPt->GetComponentLocation(),5,10,FColor::Red);
	DrawDebugSphere(GetWorld(),tPt->GetComponentLocation(),5,10,FColor::Blue);
	
	DrawDebugLine(GetWorld(),aPt->GetComponentLocation(),bPt->GetComponentLocation(),FColor::Red);
	DrawDebugLine(GetWorld(),aPt->GetComponentLocation(),tPt->GetComponentLocation(),FColor::Red);
	DrawDebugLine(GetWorld(),bPt->GetComponentLocation(),tPt->GetComponentLocation(),FColor::Red);
	
	DrawDebugSphere(GetWorld(),alerp,5,10,FColor::Blue);
	DrawDebugSphere(GetWorld(),blerp,5,10,FColor::Blue);
	DrawDebugSphere(GetWorld(),curvePt,5,10,FColor::White);
	
	if(curvePoints.Num()>=2)
	{
		for(int i=1; i< curvePoints.Num(); i++)
			DrawDebugLine(GetWorld(),curvePoints[i-1],curvePoints[i],FColor::White);
	}
	if(swordSteps.Num()>=2)
	{
		for(int i=1; i< swordSteps.Num(); i++)
		{
			DrawDebugLine(GetWorld(),swordSteps[i-1],swordSteps[i],FColor::Magenta);
			//DrawDebugSphere(GetWorld(),swordSteps[i-1],5,10,FColor::Magenta);
		}
	}
}

void ABezierCurve::DrawCurve()
{
	if(curvePoints.Num()<2)
		return;
	FVector rigCurvePt=curvePoints[0];
	swordSteps.Add(rigCurvePt);
	int i=0;
	while(i<curvePoints.Num()-1)
	{
		FVector direction = curvePoints[i+1] - curvePoints[i];
		direction.Normalize();
		rigCurvePt += direction*swordStepLength;
		swordSteps.Add(rigCurvePt);
		i++;
	}

	if(!urumiPoseable)
		return;
	if(swordSteps.Num() < urumiPoseable->GetNumBones())
		return;
	FName boneName2 = urumiPoseable->GetBoneName(0);
	urumiPoseable->SetBoneRotationByName(boneName2,FRotator(90,0,0),EBoneSpaces::WorldSpace);
	for(int j=1; j < urumiPoseable->GetNumBones() ;j++)
	{
		FName boneName = urumiPoseable->GetBoneName(j);
		urumiPoseable->SetBoneLocationByName(boneName,swordSteps[j],EBoneSpaces::WorldSpace);
		urumiPoseable->SetBoneRotationByName(boneName,FRotator(90,0,0),EBoneSpaces::WorldSpace);
		//GEngine->AddOnScreenDebugMessage(-1,50,FColor::Cyan,FString::Printf(TEXT("Bone: %s"),*boneName.ToString()));
		FVector sowrdPt = urumiPoseable->GetBoneLocation(boneName);
		GEngine->AddOnScreenDebugMessage(-1,50,FColor::Cyan,FString::Printf(TEXT("Bone: %f , %f , %f"),sowrdPt.X,sowrdPt.Y,sowrdPt.Z));
	}
}



void ABezierCurve::BeginPlay()
{
	Super::BeginPlay();
	aPt->TransformUpdated.AddUObject(this,&ABezierCurve::Temp);
	bPt->TransformUpdated.AddUObject(this,&ABezierCurve::Temp);
	tPt->TransformUpdated.AddUObject(this,&ABezierCurve::Temp);
	ResetCurve();
}

void ABezierCurve::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Drawer();
}

void ABezierCurve::Temp(USceneComponent* cmp, EUpdateTransformFlags UpdateTransformFlags, ETeleportType teleportType)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Temp value Changed.................................");
	ResetCurve();
}



