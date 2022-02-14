#include "TwinStubber.h"


ATwinStubber::ATwinStubber(){
	LeftMuzzle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left_Muzzle"));
	RightMuzzle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right_Muzzle"));
	ActiveMuzzle = LeftMuzzle;
}
AWalker* ATwinStubber::FindEnemy() {
	return this->FindAnyEnemy();
}
void ATwinStubber::OnConstruction(const FTransform & Transform) {
	ATurrel::OnConstruction(Transform);
	if (Head->GetSocketByName(Left_Muzzle_Socket_Name)) {
		LeftMuzzle->AttachToComponent(Head, FAttachmentTransformRules::SnapToTargetIncludingScale, Left_Muzzle_Socket_Name);
	}
	else {
		LeftMuzzle->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		UE_LOG(LogTemp, Error, TEXT("Muzzle Socket not found"));
	}
	if (Head->GetSocketByName(Right_Muzzle_Socket_Name)) {
		RightMuzzle->AttachToComponent(Head, FAttachmentTransformRules::SnapToTargetIncludingScale, Right_Muzzle_Socket_Name);
	}
	else {
		RightMuzzle->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		UE_LOG(LogTemp, Error, TEXT("Muzzle Socket not found"));
	}
}
void ATwinStubber::BeginPlay() {
	ATurrel::BeginPlay();
	DShift.Y = ShiftDepth / ShiftSteps;
	ShiftDelay = shoot_time / (ShiftSteps + 0.5);
	reload_time = shoot_time;
}
void ATwinStubber::StartRotate() {
	float Yaw = Target_Rotation.Yaw;
	float Pitch = Target_Rotation.Pitch;
	float Roll = Target_Rotation.Roll;
	this->SetActorRotation(FRotator(0, Yaw-90.0, 0));
	Head->SetRelativeRotation(FRotator(0, 0, -Pitch));
}
void ATwinStubber::FireToEnemy() {
	isleft = isleft ^ true;
	if (isleft) {
		ActiveMuzzle = LeftMuzzle;
	}
	else {
		ActiveMuzzle = RightMuzzle;
	}
	ActiveMuzzleLoc = FVector(0, 0, 0);
	if (IsValid(Fire_Particle) && IsValid(PreferedEnemy)) {
		FVector F_Loc = ActiveMuzzle->GetSocketLocation(Fire_Socket_Name);
		FVector Enemy_Loc = PreferedEnemy->GetActorLocation();
		PlaceParticleLine(F_Loc, Enemy_Loc, Fire_Particle, this);
	}
	time_left = ShiftDelay;
}
void ATwinStubber::ProceedFire(float delta_seconds) {
	time_left -= delta_seconds;
	if (time_left > 0) {
		return;
	}
	time_left = ShiftDelay;
	ActiveMuzzleLoc += DShift;
	ActiveMuzzle->SetRelativeLocation(ActiveMuzzleLoc);
}
void ATwinStubber::Reload() {
	time_left = ShiftDelay;
}
void ATwinStubber::ProceedReload(float delta_seconds) {
	time_left -= delta_seconds;
	if (time_left > 0) {
		return;
	}
	time_left = ShiftDelay;
	ActiveMuzzleLoc -= DShift;
	ActiveMuzzle->SetRelativeLocation(ActiveMuzzleLoc);
}