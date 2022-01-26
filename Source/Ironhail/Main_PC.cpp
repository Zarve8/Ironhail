#pragma once
#include "Main_PC.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "TurrelBasement.h"


// ++++++++++ Constructors ++++++++++
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
	TFinder = NewObject<ATurrelClassFinder>(); //Class to find Turrel Classes
	PrimaryActorTick.bCanEverTick = true;
}
void AMain_PC::BeginPlay() {
	Super::BeginPlay();
	CreateMenuBar();
	UWidgetBlueprintLibrary::SetInputMode_GameAndUI(this, false, false);
}
void AMain_PC::Tick(float DealtaTime) {

}
// ++++++++++ Menu Widgets Show/Hide ++++++++++
void AMain_PC::HideAllWidgets() {

}
void AMain_PC::CreateMenuBar() {
	if (IsValid(MenuBarClass)) {
		MenuBar = CreateWidget<UUserWidget>(this, MenuBarClass);
		MenuBar->AddToPlayerScreen(5);
	}
}
void AMain_PC::ShowTurrelWidget(TEnumAsByte<Turel> TurrelType, int level) {
	TurrelShowCaseData = ExternalDataFabric(TurrelType);
	if (IsValid(TurrelShowCaseClass)) {
		TurrelShowCase = CreateWidget<UUserWidget>(this, TurrelShowCaseClass);
		TurrelShowCase->AddToPlayerScreen(6);
	}
	if (IsValid(TurrelShowCase)) {
		UE_LOG(LogTemp, Error, TEXT("Showcase added"));
	}
}
void AMain_PC::HideTurrelWidget() {
	if (IsValid(this->TurrelShowCase)) {
		TurrelShowCase->RemoveFromParent();
		TurrelShowCase->Destruct();
		TurrelShowCase = nullptr;
	}
}
void AMain_PC::ShowMissionsWidget() {

}
void AMain_PC::ShowPowerUpsWidget() {

}
// TODO REDO
void AMain_PC::ShowBuildWidget() {
	for (int i = 0; i < 8; i++) {
		BuildArrayData.Add(ExternalDataFabric(E_Empty));
	}
	if (IsValid(MenuBuildClass)) {
		this->MenuBuildWidget = CreateWidget<UUserWidget>(this, MenuBuildClass);
		this->MenuBuildWidget->AddToPlayerScreen(3);
	}
}
void AMain_PC::HideBuildWidget() {
	if (IsValid(this->MenuBuildWidget)) {
		MenuBuildWidget->RemoveFromParent();
		MenuBuildWidget->Destruct();
		TurrelShowCase = nullptr;
	}
	BuildArrayData.Empty();
}
//
ATurrelExternalData*  AMain_PC::ExternalDataFabric(TEnumAsByte<Turel> TurrelType) {
	return NewObject<AProxyData_ED>();
}
// ++++++++++ Pressed in Widgets ++++++++++
void AMain_PC::BuildButtonPressed() {
	switch (CurrentState) {
	case E_InBuildWidget:
		HideBuildWidget();
		CurrentState = E_Playing;
		return;
	case E_Playing:
		ShowBuildWidget();
		CurrentState = E_InBuildWidget;
		return;
	default:
		HideAllWidgets();
		ShowBuildWidget();
		CurrentState = E_InBuildWidget;
	}
}
void AMain_PC::MissionButtonPressed() {

}
void AMain_PC::PowerUpButtonPressed() {

}
void AMain_PC::BuyPressed() {

}
void AMain_PC::MovePressed() {
	if (CurrentState == E_SearchingPlaceToMove) return;
	CurrentState = E_SearchingPlaceToMove;
	SetAllForPlacement();
}
void AMain_PC::SellPressed() {

}
// ++++++++++ Input From Basements ++++++++++
void AMain_PC::ScreenTouched() {
	ATurrelBasement* A = Cast<ATurrelBasement>(ActiveBasement);
	switch (CurrentState) {
	case E_ShowingTurrel:
		HideTurrelWidget();
		A->Deactivate();
		CurrentState = E_Playing;
		return;
	default:
		return;
	}
}
//
void AMain_PC::TurrelTouched(AActor* NewBase) {
	ATurrelBasement* A = Cast<ATurrelBasement>(ActiveBasement);
	ATurrelBasement* B = Cast<ATurrelBasement>(NewBase);
	switch(CurrentState) {
	case E_Playing:
		if (B->ShowActiveTurrel()) {
			CurrentState = E_ShowingTurrel;
			ShowTurrelWidget(B->TurrelType, B->level);
			ActiveBasement = NewBase;
			B->ShowActiveTurrel();
		}
		return;
	case E_SearchingPlaceToMove:
		if (ensure(A != B) && (B->TurrelType == E_Empty)) {
			CurrentState = E_Playing;
			B->SpawnTurrel(A->TurrelType);
			A->DestroyTurrel();
			HideTurrelWidget();
			DeactivateAll();
		}
		return;
	case E_ShowingTurrel:
		if (ensure(A != B) && (B->TurrelType != E_Empty)) {
			if (B->ShowActiveTurrel()) {
				HideTurrelWidget();
				ActiveBasement = NewBase;
				ShowTurrelWidget(B->TurrelType, B->level);
				A->Deactivate();
			}
		}
		return;
		//TODO
	case E_SearchingPlaceToBuild:
		return;
	default:
		if (B->ShowActiveTurrel()) {
			HideAllWidgets();
			CurrentState = E_ShowingTurrel;
			ActiveBasement = NewBase;
			ShowTurrelWidget(B->TurrelType, B->level);
		}
		return;
	}
}
// ++++++++++ State Actions ++++++++++
void AMain_PC::SetAllForPlacement() {
	UE_LOG(LogTemp, Error, TEXT("SetAllForPlacement"));
	TArray<AActor*> BasesFound;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATurrelBasement::StaticClass(), BasesFound);
	int index = 0;
	while (BasesFound.IsValidIndex(index)) {
		ATurrelBasement* B = Cast<ATurrelBasement>(BasesFound[index]);
		B->ShowForPlacement();
		index++;
	}
}
void AMain_PC::DeactivateAll() {
	TArray<AActor*> BasesFound;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATurrelBasement::StaticClass(), BasesFound);
	int index = 0;
	while (BasesFound.IsValidIndex(index)) {
		ATurrelBasement* B = Cast<ATurrelBasement>(BasesFound[index]);
		B->Deactivate();
		index++;
	}
}
