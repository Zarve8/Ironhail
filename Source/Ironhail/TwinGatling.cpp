#include "TwinGatling.h"


ATwinGatling::ATwinGatling(): ATurrel(){
	LeftGatling = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftGatling"));
	RightGatling = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightGatling"));
}
void ATwinGatling::OnConstruction(const FTransform & Transform) {
	ATurrel::OnConstruction(Transform);
	LeftGatling->AttachToComponent(Head, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("G_1"));
	RightGatling->AttachToComponent(Head, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("G_2"));
}
void ATwinGatling::BeginPlay() {
	ATurrel::BeginPlay();
	GatlingSpeedRotator = (180 / MuzzlesCount) / shoot_time;
	RotateAngle = 180 / MuzzlesCount;
}
AWalker* ATwinGatling::FindEnemy() {
	return this->FindAnyEnemy();
}
void ATwinGatling::FireToEnemy() {
	GatlingRotator.Roll = GatlingTargetRotate;
	GatlingTargetRotate += RotateAngle;
	if (IsValid(Fire_Particle) && IsValid(PreferedEnemy)) {
		FVector F_Loc = Head->GetSocketLocation("F_1");
		FVector Enemy_Loc = PreferedEnemy->GetActorLocation();
		PlaceParticleLine(F_Loc, Enemy_Loc, Fire_Particle, this);
		F_Loc = Head->GetSocketLocation("F_2");
		PlaceParticleLine(F_Loc, Enemy_Loc, Fire_Particle, this);
	}
}
void ATwinGatling::ProceedFire(float delta_seconds) {
	GatlingRotator.Roll += GatlingSpeedRotator * delta_seconds;
	LeftGatling->SetRelativeRotation(GatlingRotator);
	RightGatling->SetRelativeRotation(GatlingRotator);
}
void ATwinGatling::StartRotate() {
	float Yaw = Target_Rotation.Yaw;
	float Pitch = Target_Rotation.Pitch;
	float Roll = Target_Rotation.Roll;
	this->SetActorRotation(FRotator(0, Yaw - 90.0, 0));
	Head->SetRelativeRotation(FRotator(0, 0, -Pitch));
}

