#include "TwinStubber.h"

ATwinStubber::ATwinStubber(){
	LeftMuzzle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left_Muzzle"));
	RightMuzzle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right_Muzzle"));
	ActiveMuzzle = LeftMuzzle;
	//AdditionalRotation = FRotator(90, 90, 90);
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
void ATwinStubber::FireToEnemy() {

}
void ATwinStubber::ProceedFire(float delta_seconds) {

}
void ATwinStubber::StartRotate() {
	float Yaw = Target_Rotation.Yaw;
	float Pitch = Target_Rotation.Pitch;
	float Roll = Target_Rotation.Roll;
	this->SetActorRotation(FRotator(0, Yaw-90.0, 0));
	Head->SetRelativeRotation(FRotator(0, 0, -Pitch));
}
