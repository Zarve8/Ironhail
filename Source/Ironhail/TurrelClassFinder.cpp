#include "TurrelClassFinder.h"
#include "UObject/ConstructorHelpers.h"


 ATurrelClassFinder::ATurrelClassFinder() {
	 /*
	 PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FClassFinder<ATurrel> SObject00(TEXT("/Game/Blueprints/Turrels/AutoCannon_2_BP"));
	if (SObject00.Succeeded()) {
		Empty = SObject00.Class;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Turrel Class not found"));
	}
	static ConstructorHelpers::FClassFinder<ATurrel> SObject0(TEXT("/Game/Blueprints/Turrels/AutoCannon_2_BP"));
	if (SObject0.Succeeded()) {
		AutoCannon_2 = SObject0.Class;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Turrel Class not found"));
	}
	static ConstructorHelpers::FClassFinder<ATurrel> SObject1(TEXT("/Game/Blueprints/Turrels/AutoCannon_3_BP"));
	if (SObject1.Succeeded()) {
		AutoCannon_3 = SObject1.Class;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Turrel Class not found"));
	}
	static ConstructorHelpers::FClassFinder<ATurrel> SObject2(TEXT("/Game/Blueprints/Turrels/AutoCannon_4_BP"));
	if (SObject2.Succeeded()) {
		AutoCannon_4 = SObject2.Class;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Turrel Class not found"));
	}
	static ConstructorHelpers::FClassFinder<ATurrel> SObject3(TEXT("/Game/Blueprints/Turrels/AutoCannon_5_BP"));
	if (SObject3.Succeeded()) {
		AutoCannon_5 = SObject3.Class;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Turrel Class not found"));
	}
	static ConstructorHelpers::FClassFinder<ATurrel> SObject4(TEXT("/Game/Blueprints/Turrels/AutoCannon_6_BP"));
	if (SObject4.Succeeded()) {
		AutoCannon_6 = SObject4.Class;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Turrel Class not found"));
	}
	static ConstructorHelpers::FClassFinder<ATurrel> SObject5(TEXT("/Game/Blueprints/Turrels/RocketPod_4_BP"));
	if (SObject5.Succeeded()) {
		RocketPod_4 = SObject5.Class;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Turrel Class not found"));
	}
	static ConstructorHelpers::FClassFinder<ATurrel> SObject6(TEXT("/Game/Blueprints/Turrels/RocketPod_5_BP"));
	if (SObject6.Succeeded()) {
		RocketPod_5 = SObject6.Class;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Turrel Class not found"));
	}
	static ConstructorHelpers::FClassFinder<ATurrel> SObject7(TEXT("/Game/Blueprints/Turrels/RocketPod_6_BP"));
	if (SObject7.Succeeded()) {
		RocketPod_6 = SObject7.Class;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Turrel Class not found"));
	}
	static ConstructorHelpers::FClassFinder<ATurrel> SObject8(TEXT("/Game/Blueprints/Turrels/FrostCannon_5_BP"));
	if (SObject8.Succeeded()) {
		FrostCannon_5 = SObject8.Class;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Turrel Class not found"));
	}
	static ConstructorHelpers::FClassFinder<ATurrel> SObject9(TEXT("/Game/Blueprints/Turrels/FrostCannon_6_BP"));
	if (SObject9.Succeeded()) {
		FrostCannon_6 = SObject9.Class;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Turrel Class not found"));
	}
	static ConstructorHelpers::FClassFinder<ATurrel> SObject10(TEXT("/Game/Blueprints/Turrels/LongArm_3_BP"));
	if (SObject10.Succeeded()) {
		LongArm_3 = SObject10.Class;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Turrel Class not found"));
	}
	static ConstructorHelpers::FClassFinder<ATurrel> SObject11(TEXT("/Game/Blueprints/Turrels/LongArm_4_BP"));
	if (SObject11.Succeeded()) {
		LongArm_4 = SObject11.Class;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Turrel Class not found"));
	}
	static ConstructorHelpers::FClassFinder<ATurrel> SObject12(TEXT("/Game/Blueprints/Turrels/LongArm_5_BP"));
	if (SObject12.Succeeded()) {
		LongArm_5 = SObject12.Class;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Turrel Class not found"));
	}
	static ConstructorHelpers::FClassFinder<ATurrel> SObject13(TEXT("/Game/Blueprints/Turrels/LongArm_6_BP"));
	if (SObject13.Succeeded()) {
		LongArm_6 = SObject13.Class;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Turrel Class not found"));
	}
	*/
}

TSubclassOf<ATurrel> ATurrelClassFinder::GetTurrelClassByEnum(TEnumAsByte<Turel> Type) {
	switch (Type) {
	case E_AutoCannon_2:
		return AutoCannon_2;
	case E_AutoCannon_3:
		return AutoCannon_2;
	case E_AutoCannon_4:
		return AutoCannon_2;
	case E_AutoCannon_5:
		return AutoCannon_2;
	case E_AutoCannon_6:
		return AutoCannon_2;
	case E_RocketPod_4:
		return RocketPod_4;
	case E_RocketPod_5:
		return RocketPod_5;
	case E_RocketPod_6:
		return RocketPod_6;
	case E_LongArm_3:
		return LongArm_3;
	case E_LongArm_4:
		return LongArm_4;
	case E_LongArm_5:
		return LongArm_5;
	case E_LongArm_6:
		return LongArm_6;
	case E_Laser_5:
		return Laser_5;
	case E_Laser_6:
		return Laser_6;
	case E_FrostCannon_5:
		return FrostCannon_5;
	case E_FrostCannon_6:
		return FrostCannon_6;
	default:
		return Empty;
	}
	return Empty;
}


