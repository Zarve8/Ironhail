#pragma once
#include "Main_PC.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


AMain_PC::AMain_PC() {
	//Load Widget BlueprintClasses
	static ConstructorHelpers::FClassFinder<UUserWidget> SObject0(TEXT("/Game/Blueprints/Widgets/MenuBar_W")); 
	if (SObject0.Succeeded()) {
		MenuBarClass = SObject0.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> SObject1(TEXT("/Game/Blueprints/Widgets/TurrelShowCase_W"));
	if (SObject1.Succeeded()) {
		TurrelShowCaseClass = SObject1.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> SObject2(TEXT("/Game/Blueprints/Widgets/MenuBuild_W"));
	if (SObject2.Succeeded()) {
		MenuBuildClass = SObject2.Class;
	}
	PrimaryActorTick.bCanEverTick = true;
}
void AMain_PC::BeginPlay() {
	Super::BeginPlay();
	CreateMenuBar();
	UWidgetBlueprintLibrary::SetInputMode_GameAndUI(this, false, true);
}
void AMain_PC::Tick(float DealtaTime) {

}
void AMain_PC::CreateMenuBar() {
	if (IsValid(MenuBarClass)) {
		MenuBar = CreateWidget<UUserWidget>(this, MenuBarClass);
		MenuBar->AddToPlayerScreen();
	}
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
void AMain_PC::ShowPowerUpsWidget() {

}
void AMain_PC::ShowBuildWidget() {
	BuildArrayData.Empty();
	for (int i = 0; i < 8; i++) {
		BuildArrayData.Add(ExternalDataFabric(E_Empty));
		UE_LOG(LogTemp, Warning, TEXT("U"));
	}
	if (IsValid(MenuBuildClass)) {
		MenuBuild = CreateWidget<UUserWidget>(this, MenuBuildClass);
		MenuBuild->AddToPlayerScreen();
	}
	UE_LOG(LogTemp, Warning, TEXT("Created Build Menu"));
}
ATurrelExternalData*  AMain_PC::ExternalDataFabric(TEnumAsByte<Turel> TurrelType) {
	return NewObject<AProxyData_ED>();
}