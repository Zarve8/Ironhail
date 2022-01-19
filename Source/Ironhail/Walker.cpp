#include "Walker.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


AWalker::AWalker()
{
	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	
	PrimaryActorTick.bCanEverTick = true;

}
void AWalker::BeginPlay()
{
	Body->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TArray<AActor*> Pathes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APathPivot::StaticClass(), Pathes);
	if (Pathes.IsValidIndex(0)) {
		this->path = Cast<APathPivot>(Pathes[0]);
	}
	else {
		Destroy();
	}
	Super::BeginPlay();
	
}
Action_AM* AWalker::GetBaseAction() {
	return new DelayBeforeMove_AM(this, 0.1);
}
void AWalker::Tick(float DeltaTime)
{
	ActionTick(DeltaTime);
	Super::Tick(DeltaTime);

}
void AWalker::Die() {
	this->Destroy();
}
void AWalker::SufferDamage(float damage) {
	health -= damage * armour_cof;
	if (health <= 0) {
		this->Die();
	}
}
void AWalker::RotateToDirection(FVector Forward) {
	FRotator R = Forward.Rotation();
	//this->SetActorRotation(FRotator(0, 0, R.Yaw));
	SetActorRotation(R);
}
