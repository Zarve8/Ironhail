#include "QuadStubber.h"


AQuadStubber::AQuadStubber(){
	Muzzle_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Muzzle_1"));
	Muzzle_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Muzzle_2"));
	Muzzle_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Muzzle_3"));
	Muzzle_4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Muzzle_4"));
	Mag_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mag_1"));
	Mag_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mag_2"));
	Mag_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mag_3"));
	Mag_4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mag_4"));
	ActiveMuzzle = Muzzle_4;
}
AWalker* AQuadStubber::FindEnemy() {
	return this->FindAnyEnemy();
}
void AQuadStubber::OnConstruction(const FTransform & Transform) {
	ATurrel::OnConstruction(Transform);
	Muzzle_1->AttachToComponent(Head, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("M_1"));
	Muzzle_2->AttachToComponent(Head, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("M_2"));
	Muzzle_3->AttachToComponent(Head, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("M_3"));
	Muzzle_4->AttachToComponent(Head, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("M_4"));
	Mag_1->AttachToComponent(Head, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Mag_1"));
	Mag_2->AttachToComponent(Head, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Mag_2"));
	Mag_3->AttachToComponent(Head, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Mag_3"));
	Mag_4->AttachToComponent(Head, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Mag_4"));
}
void AQuadStubber::BeginPlay() {
	ATurrel::BeginPlay();
	DShift.X = ShiftDepth / ShiftSteps;
	ShiftDelay = shoot_time / (ShiftSteps + 0.5);
	reload_time = shoot_time;
}
void AQuadStubber::FireToEnemy() {
	is_2 ^= is_1;
	is_1 ^= true;
	if (is_1) {
		if (is_2) {
			ActiveMuzzle = Muzzle_4;
		}
		else {
			ActiveMuzzle = Muzzle_3;
		}
	}
	else {
		if (is_2) {
			ActiveMuzzle = Muzzle_2;
		}
		else {
			ActiveMuzzle = Muzzle_1;
		}
	}
	//
	ActiveMuzzleLoc = FVector(0, 0, 0);
	if (IsValid(Fire_Particle) && IsValid(PreferedEnemy)) {
		FVector F_Loc = ActiveMuzzle->GetSocketLocation("F_1");
		FVector Enemy_Loc = PreferedEnemy->GetActorLocation();
		PlaceParticleLine(F_Loc, Enemy_Loc, Fire_Particle, this);
	}
	time_left = ShiftDelay;
}
void AQuadStubber::ProceedFire(float delta_seconds) {
	time_left -= delta_seconds;
	if (time_left > 0) {
		return;
	}
	time_left = ShiftDelay;
	ActiveMuzzleLoc += DShift;
	ActiveMuzzle->SetRelativeLocation(ActiveMuzzleLoc);
}
void AQuadStubber::Reload() {
	time_left = ShiftDelay;
}
void AQuadStubber::ProceedReload(float delta_seconds) {
	time_left -= delta_seconds;
	//
	RotateMag(delta_seconds);
	if (time_left > 0) {
		return;
	}
	time_left = ShiftDelay;
	ActiveMuzzleLoc -= DShift;
	ActiveMuzzle->SetRelativeLocation(ActiveMuzzleLoc);
}
void AQuadStubber::RotateMag(float delta_time) {
	MagRotator.Roll += MagRotationSpeed * delta_time;
	Mag_1->SetRelativeRotation(MagRotator);
	Mag_2->SetRelativeRotation(MagRotator);
	Mag_3->SetRelativeRotation(MagRotator);
	Mag_4->SetRelativeRotation(MagRotator);
}

