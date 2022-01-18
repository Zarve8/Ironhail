#include "Walker.h"

AWalker::AWalker()
{
	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	Body->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	PrimaryActorTick.bCanEverTick = true;

}
void AWalker::BeginPlay()
{
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
	this->SetActorRotation(FRotator(0, 0, R.Yaw));
}
