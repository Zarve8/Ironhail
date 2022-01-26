#include "LongArm.h"

ALongArm::ALongArm(): ATurrel(){
	Trigger = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trigger"));
	MagShaft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shaft"));
	Mag = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mag"));
	PrimaryActorTick.bCanEverTick = true;
	Head_Scale = FVector(0.9, 0.7, 0.8);
}
void ALongArm::OnConstruction(const FTransform & Transform) {
	ATurrel::OnConstruction(Transform);
	if (Head->GetSocketByName(TEXT("Trigger_Socket"))) {
		Trigger->AttachToComponent(Head, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Trigger_Socket"));
	}
	if (Head->GetSocketByName(TEXT("Shaft_Socket"))) {
		MagShaft->AttachToComponent(Head, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Shaft_Socket"));
	}
	if (MagShaft->GetSocketByName(TEXT("Mag_Socket"))) {
		Mag->AttachToComponent(MagShaft, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Mag_Socket"));
	}
	reload_time = 0;
}
void ALongArm::BeginPlay() {
	MagRotDelta.Pitch = 360 / (mag_capacity*shoot_time);
	MagStepDelta.Pitch = 360 / (mag_capacity);
	TriggerRotDelta.Roll = 45 / shoot_time;
	BulletsLeft = mag_capacity;
	ATurrel::BeginPlay();
}
AWalker* ALongArm::FindEnemy() {
	return FindAnyEnemy();
}
void ALongArm::FireToEnemy() {
	Trigger->SetRelativeRotation(FRotator(0, 0, 0));
	Mag->SetRelativeRotation(MagTargetRot);
	MagRot = MagTargetRot;
	TriggerRot = FRotator(0, 0, 0);
	BulletsLeft -= 1;
	if (BulletsLeft <= 0) reload_time = reload_time_overrided;
	if (IsValid(Fire_Particle) && IsValid(PreferedEnemy)) {
		FVector F_Loc = Head->GetSocketLocation("F_1");
		FVector Enemy_Loc = PreferedEnemy->GetActorLocation();
		AttachParticleLine(F_Loc, Enemy_Loc, Fire_Particle, this, Head->GetSocketByName("F_1"));
	}
	MagTargetRot += MagStepDelta;
}
void ALongArm::ProceedFire(float delta_time) {
	MagRot += MagRotDelta *delta_time;
	TriggerRot += TriggerRotDelta * delta_time;
	Trigger->SetRelativeRotation(TriggerRot);
	Mag->SetRelativeRotation(MagRot);
}
void ALongArm::Reload() {
	if(BulletsLeft == 0) MagShaft->SetRelativeRotation(ShaftUpRot);
}
void ALongArm::EndReload() {
	if (BulletsLeft == 0) {
		MagShaft->SetRelativeRotation(FRotator(0, 0, 0));
		reload_time = 0;
		BulletsLeft = mag_capacity;
	}
}
void ALongArm::StartRotate() {
	float Yaw = Target_Rotation.Yaw;
	float Pitch = Target_Rotation.Pitch;
	float Roll = Target_Rotation.Roll;
	this->SetActorRotation(FRotator(0, Yaw - 90.0, 0));
	Head->SetRelativeRotation(FRotator(0, 0, -Pitch));
}

