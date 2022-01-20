#include "Laser.h"


ALaser::ALaser() : ATurrel() {

}
void ALaser::BeginPlay() {
	shoot_time = 100;
	ATurrel::BeginPlay();
}
AWalker* ALaser::FindEnemy() {
	return this->FindAnyEnemy();
}
void ALaser::FireToEnemy() {
	shoot_time = 100;
	if (IsValid(Fire_Particle) && IsValid(PreferedEnemy)) {
		FVector F_Loc = Head->GetSocketLocation("F_1");
		FVector Enemy_Loc = PreferedEnemy->GetActorLocation();
		AttachParticleLine(F_Loc, Enemy_Loc, Fire_Particle, this, Head->GetSocketByName("F_1"));
	}
}
void ALaser::FollowTarget() {
	FVector FaceLoc = Head->GetSocketLocation(Head_Face_Socket_Name);
	FVector N = FaceLoc - PreferedEnemy->GetActorLocation();
	Target_Rotation = N.Rotation();
	float Yaw = Target_Rotation.Yaw;
	float Pitch = Target_Rotation.Pitch;
	this->SetActorRotation(FRotator(0, Yaw, 0));
	Head->SetRelativeRotation(FRotator(Pitch, 0, 0));
}
void ALaser::ProceedFire(float delta_time) {
	if (IsValid(PreferedEnemy)) {
		shoot_time = 100;
		FollowTarget();
	}
	else {
		shoot_time = 0;
	}
}

