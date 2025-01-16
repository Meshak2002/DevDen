#include "TestActor.h"

ATestActor::ATestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATestActor::DelegateCall()
{
	testDelegate.Broadcast();
}

void ATestActor::overhorse()
{
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,"Overhorse");
}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	if(Implements<UTestInterface>())
		ITestInterface::Execute_BpTester(this);
}
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestActor::Tester()
{
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,FString::Printf(TEXT("Testerrrr : %d"),intemp) );
}

void ATestActor::BpTester_Implementation()
{
	
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,FString::Printf(TEXT("Lalo")) );
}

