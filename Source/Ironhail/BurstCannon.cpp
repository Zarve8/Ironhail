#include "BurstCannon.h"


ABurstCannon::ABurstCannon(): ATurrel() {
	Gatling = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gatling"));
}
void ABurstCannon::OnConstruction(const FTransform & Transform) {
	ATurrel::OnConstruction(Transform);
	Gatling->AttachToComponent(Head, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("G_1"));
}
void ABurstCannon::BeginPlay() {
	ATurrel::BeginPlay();
	GatlingSpeedRotator = (180 / MuzzlesCount) / shoot_time;
	RotateAngle = 180 / MuzzlesCount;
}
AWalker* ABurstCannon::FindEnemy() {
	return this->FindAnyEnemy();
}
void ABurstCannon::FireToEnemy() {
	GatlingRotator.Roll = GatlingTargetRotate;
	GatlingTargetRotate += RotateAngle;
	if (IsValid(Fire_Particle) && IsValid(PreferedEnemy)) {
		FVector F_Loc = Head->GetSocketLocation("F_1");
		FVector Enemy_Loc = PreferedEnemy->GetActorLocation();
		PlaceParticleLine(F_Loc, Enemy_Loc, Fire_Particle, this);
	}
}
void ABurstCannon::ProceedFire(float delta_seconds) {
	GatlingRotator.Roll += GatlingSpeedRotator * delta_seconds;
	Gatling->SetRelativeRotation(GatlingRotator);
}