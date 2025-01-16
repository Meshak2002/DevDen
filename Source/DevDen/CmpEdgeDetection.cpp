#include "CmpEdgeDetection.h"

#include "Kismet/GameplayStatics.h"

UCmpEdgeDetection::UCmpEdgeDetection() : rayAngleThreshold(30), mAngleDecrementer(0) , tAngleDecrementer(0)
 , channel(ECC_WorldStatic)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCmpEdgeDetection::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCmpEdgeDetection::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckForEdge();
}

void UCmpEdgeDetection::CheckForEdge()
{
	GetCameraTransform();
	FRotator mRayRotation = FRotator(CameraRotation.Pitch   ,	CameraRotation.Yaw,CameraRotation.Roll);
	mRay = camRay+mRayRotation.Vector()*3500;
	FRotator tRayRotation = FRotator(CameraRotation.Pitch + rayAngleThreshold ,	CameraRotation.Yaw,CameraRotation.Roll);
	tRay = camRay+tRayRotation.Vector()*3500;
	FRotator bRayRotation = FRotator(CameraRotation.Pitch - rayAngleThreshold	,	CameraRotation.Yaw,CameraRotation.Roll);
	bRay = camRay+bRayRotation.Vector()*3500;
	
	DrawDebugLine(GetWorld(),camRay,bRay,FColor::Red);
	DrawDebugLine(GetWorld(),camRay,tRay,FColor::Red);
	DrawDebugLine(GetWorld(),camRay,mRay,FColor::Red);
	
	if(!IsBtraceCollided(CameraRotation))
	{
		GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,"BottomTrace Not Colliding");
		return;
	}
	
	bool mTrace= GetWorld()->LineTraceSingleByChannel(RayHit,camRay,mRay,channel);
	if(!mTrace)
	{
		GEngine->AddOnScreenDebugMessage(-1,1,FColor::Blue,"Mid  Trace Not Colliding");
		MidTraceDetectEdge(CameraRotation);
		return;
	}
	
	bool tTrace= GetWorld()->LineTraceSingleByChannel(RayHit,camRay,tRay,channel);
	if(!tTrace)
	{
		GEngine->AddOnScreenDebugMessage(-1,1,FColor::Cyan,"Top Trace Not Colliding");
		TopTraceDetectEdge(CameraRotation);
	}
	/*
	DrawDebugSphere(GetWorld(),mRayEnd,20,10,FColor::Blue);
	DrawDebugSphere(GetWorld(),tRayEnd,20,10,FColor::Blue);*/
}

void UCmpEdgeDetection::GetCameraTransform()
{
	APlayerController* controller =  GetWorld()->GetFirstPlayerController();
	if(!controller)
		return;
	controller->GetPlayerViewPoint(CameraLocation,CameraRotation);
	camRay = CameraLocation+CameraRotation.Vector()*500;
}

bool UCmpEdgeDetection::IsBtraceCollided(FRotator cameraRot)
{
	bool bTrace = GetWorld()->LineTraceSingleByChannel(RayHit,camRay,bRay,channel);
	return bTrace;
	//GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,"BottomTrace");
}

void UCmpEdgeDetection::MidTraceDetectEdge(FRotator cameraRot)
{
	FRotator mRayRotation;
	FVector midTraceRay = mRay;
	int i=1;
	float substep = 1/rayAngleThreshold;
	do
	{
		mAngleDecrementer  = rayAngleThreshold*(substep*i);
		mRayRotation = FRotator(cameraRot.Pitch - mAngleDecrementer  ,cameraRot.Yaw,cameraRot.Roll);
		midTraceRay = camRay+mRayRotation.Vector()*3500;
		i++;
		if(i>MAX_ITERATIONS) break;
		//GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,FString::Printf(TEXT("MediumTraceFalse %f"),tRayEnd.Z));
	}while (!GetWorld()->LineTraceSingleByChannel(RayHit,camRay,midTraceRay,channel));
	
	//DrawDebugLine(GetWorld(),camRay,midTraceRay,FColor::Blue);
	edgePt=RayHit.ImpactPoint;
	DrawDebugSphere(GetWorld(),edgePt,50,20,FColor::Red);
	
}

void UCmpEdgeDetection::TopTraceDetectEdge(FRotator cameraRot)
{
	FRotator tRayRotation;
	FVector topTraceRay = tRay;
	int j=1;
	float substep = 1/rayAngleThreshold;
	do
	{
		tAngleDecrementer = rayAngleThreshold*(substep*j);
		tRayRotation = FRotator(cameraRot.Pitch + rayAngleThreshold - tAngleDecrementer ,cameraRot.Yaw,cameraRot.Roll);
		topTraceRay = camRay+tRayRotation.Vector()*3500;
		j++;
		if(j>MAX_ITERATIONS) break;
		//GEngine->AddOnScreenDebugMessage(-1,1,FColor::Red,FString::Printf(TEXT("TopTraceFalse %f"),tRayEnd.Z));
	}while(!GetWorld()->LineTraceSingleByChannel(RayHit,camRay,topTraceRay,channel));

	//DrawDebugLine(GetWorld(),camRay,topTraceRay,FColor::Green);
	edgePt=RayHit.ImpactPoint;
	DrawDebugSphere(GetWorld(),edgePt,50,20,FColor::Red);
	
}

