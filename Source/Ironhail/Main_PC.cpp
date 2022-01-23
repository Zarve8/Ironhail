#pragma once
#include "Main_PC.h"


AMain_PC::AMain_PC() {
	static ConstructorHelpers::FClassFinder<UUserWidget> SObject1(TEXT("/Game/Blueprints/Widgets/TurrelShowCase_W")); //Load Widget BlueprintClasses
	if (SObject1.Succeeded()) {
		TurrelShowCaseClass = SObject1.Class;
	}
	PrimaryActorTick.bCanEverTick = true;
}
void AMain_PC::BeginPlay() {
	Super::BeginPlay();
}
void AMain_PC::Tick(float DealtaTime) {

}
void AMain_PC::HideTurrelWidget() {

}
void AMain_PC::ShowTurrelWidget(TEnumAsByte<Turel> TurrelType, int level) {
	TurrelShowCaseData = ExternalDataFabric(TurrelType);
	if (IsValid(TurrelShowCaseClass)) {
		TurrelShowCase = CreateWidget<UUserWidget>(this, TurrelShowCaseClass);
		TurrelShowCase->AddToPlayerScreen();
	}
}
void AMain_PC::ShowMissionsWidget() {

}
void AMain_PC::HideMissionsWidget() {

}
void AMain_PC::ShowPowerUpsWidget() {

}
void AMain_PC::HidePowerUpsWidget() {

}
void AMain_PC::ShowBuildWidget() {

}
void AMain_PC::HideBuildWidget() {

}
ATurrelExternalData*  AMain_PC::ExternalDataFabric(TEnumAsByte<Turel> TurrelType) {
	return NewObject<ATurrelExternalData>();
}