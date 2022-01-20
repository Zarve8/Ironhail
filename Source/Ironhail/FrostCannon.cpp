#include "FrostCannon.h"


AFrostCannon::AFrostCannon(): ATurrel() {
	Beam = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Beam"));
}
void AFrostCannon::OnConstruction(const FTransform & Transform) {
	ATurrel::OnConstruction(Transform);
	Beam->AttachToComponent(Head, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Head_Socket"));
}
AWalker* AFrostCannon::FindEnemy() {
	return this->FindAnyEnemy();
}
void AFrostCannon::FireToEnemy() {
	if (IsValid(Fire_Particle) && IsValid(PreferedEnemy)) {
		FVector F_Loc = Head->GetSocketLocation(Fire_Socket_Name);
		FVector Enemy_Loc = PreferedEnemy->GetActorLocation();
		PlaceParticleLine(F_Loc, Enemy_Loc, Fire_Particle, this);
	}
}
void AFrostCannon::StartRotate() {
	float Yaw = Target_Rotation.Yaw;
	float Pitch = Target_Rotation.Pitch;
	float Roll = Target_Rotation.Roll;
	this->SetActorRotation(FRotator(0, Yaw - 90.0, 0));
	Head->SetRelativeRotation(FRotator(0, 0, -Pitch));
}



