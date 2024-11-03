
#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "Engine.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	FAttachmentTransformRules rules{
		EAttachmentRule::SnapToTarget,EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld, false};
	boxCollider->AttachToComponent(GetMesh(),rules,"hand_rSocket");

	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	animInstance = GetMesh()->GetAnimInstance();
	
	boxCollider->SetCollisionProfileName("OverlapAllDynamic");
	boxCollider->SetNotifyRigidBodyCollision(true);
	boxCollider->OnComponentBeginOverlap.AddDynamic(this,&AEnemy::OnAttackOverlapBegin);
	boxCollider->OnComponentEndOverlap.AddDynamic(this,&AEnemy::OnAttackOverlapEnd);
}

// Called every frame
void AEnemy::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	
}

UBehaviorTree* AEnemy::GetBahaviorTree()
{
	if (behaviorTree)
		return behaviorTree;
	return nullptr;
}

void AEnemy::PlayAttackAnim()
{
	if(!animInstance)
		return;
	if(!animInstance->Montage_IsPlaying(attackAnim))
		PlayAnimMontage(attackAnim);
}

void AEnemy::Die()
{
	//GetController()->Destroy();

	
	if(boxCollider)
		boxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	USkeletalMeshComponent* MeshComponent = GetMesh();
	// Loop through all components attached to this character
	for (UActorComponent* Component : GetComponents())
	{
		// Skip the mesh component to keep it intact
		if (Component != MeshComponent)
		{
			Component->DestroyComponent();
		}
	}
}

void AEnemy::OnAttackOverlapBegin(
	UPrimitiveComponent* const OverlappedComponent,
	AActor* const OtherActor,
	UPrimitiveComponent* const OtherComponent,
	int const OtherBodyIndex,
	bool const FromSweep,
	FHitResult const& SweepResult)
{
	if(OtherActor==this)
		return;
}

void AEnemy::OnAttackOverlapEnd(UPrimitiveComponent* const OverlappedComponent, AActor* const OtherActor,
	UPrimitiveComponent* OtherComponent, int const OtherBodyIndex)
{
	
	if(OtherActor==this)
		return;
}


