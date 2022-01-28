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
	static ConstructorHelpers::FClassFinder<UUserWidget> SObject3(TEXT("/Game/Blueprints/Widgets/MergeMenu_W"));
	if (SObject3.Succeeded()) {
		MergeMenuClass = SObject3.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> SObject4(TEXT("/Game/Blueprints/Widgets/DarkTone_W"));
	if (SObject4.Succeeded()) {
		DarkToneClass = SObject4.Class;
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
	HideTurrelWidget();
	HideBuildWidget();
	HideMergeWidget();
	HideDarkToneWidget();
}
void AMain_PC::CreateMenuBar() {
	if (IsValid(MenuBarClass)) {
		MenuBar = CreateWidget<UUserWidget>(this, MenuBarClass);
		MenuBar->AddToPlayerScreen(5);
	}
}
void AMain_PC::ShowTurrelWidget(TEnumAsByte<Turel> TurrelType, ATurrelInternalData* TData) {
	TurrelShowCaseData = ExternalDataFabric(TurrelType);
	ActiveTurrelData = TData;
	if (IsValid(TurrelShowCaseClass)) {
		TurrelShowCase = CreateWidget<UUserWidget>(this, TurrelShowCaseClass);
		TurrelShowCase->AddToPlayerScreen(6);
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
void AMain_PC::ShowDarkToneWidget() {
	if (IsValid(DarkToneClass)) {
		DarkToneWidget = CreateWidget<UUserWidget>(this, DarkToneClass);
		DarkToneWidget->AddToPlayerScreen(0);
	}
}
void AMain_PC::HideDarkToneWidget() {
	if (IsValid(this->DarkToneWidget)) {
		DarkToneWidget->RemoveFromParent();
		DarkToneWidget->Destruct();
		DarkToneWidget = nullptr;
	}
}
// TODO REDO
void AMain_PC::ShowBuildWidget() {
	BuildArrayData.Empty();
	for (int i = 0; i < 8; i++) {
		BuildArrayData.Add(ExternalDataFabric(E_AutoCannon_5));
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
		MenuBuildWidget = nullptr;
	}
}
void AMain_PC::ShowMergeWidget() {
	BuildArrayData.Empty();
	if (!IsValid(ActiveBasement)) return;
	ATurrelBasement* B = Cast<ATurrelBasement>(ActiveBasement);
	ATurrelExternalData* D = ExternalDataFabric(B->TurrelType);
	TArray<TEnumAsByte<Turel>> T = D->ChildTurrels;
	int index = 0;
	while (T.IsValidIndex(index)) {
		BuildArrayData.Add(ExternalDataFabric(T[index]));
		index++;
	}
	if (IsValid(MergeMenuClass)) {
		this->MergeWidget = CreateWidget<UUserWidget>(this, MergeMenuClass);
		this->MergeWidget->AddToPlayerScreen(3);
	}
	
}
void AMain_PC::HideMergeWidget() {
	if (IsValid(this->MenuBuildWidget)) {
		MergeWidget->RemoveFromParent();
		MergeWidget->Destruct();
		MergeWidget = nullptr;
	}
}
// ++++++++++ Fabrica to get TurrelExternalData ++++++++++
ATurrelExternalData*  AMain_PC::ExternalDataFabric(TEnumAsByte<Turel> TurrelType) {
	TSubclassOf<ATurrelExternalData> T = TFinder->GetDataClassByEnum(TurrelType);
	ATurrelExternalData* E = NewObject<ATurrelExternalData>(this, T);
	return E;
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
void AMain_PC::BuyPressed(ATurrelExternalData* Data) {
	if (!IsValid(Data)) return;
	if (Data->TurrelType == E_Empty) return;
	switch (CurrentState) {
	case E_InBuildWidget:
		CurrentState = E_SearchingPlaceToBuild;
		SetAllForPlacement();
		ShowDarkToneWidget();
		TurrelShowCaseData = Data;
		return;
	default:
		return;
	}
}
void AMain_PC::MissionButtonPressed() {

}
void AMain_PC::PowerUpButtonPressed() {

}
void AMain_PC::MovePressed() {
	if (CurrentState == E_SearchingPlaceToMove) return;
	CurrentState = E_SearchingPlaceToMove;
	ShowDarkToneWidget();
	SetAllForPlacement();
}
void AMain_PC::SellPressed() {

}
void AMain_PC::GiveSoftCoins(int amount) {
	SoftCoins -= amount;
}
void AMain_PC::MergePressed(TEnumAsByte<Turel> TType, int rang) {
	CurrentState = E_SearchingPlaceToMerge;
	ShowDarkToneWidget();
	TArray<AActor*> BasesFound;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATurrelBasement::StaticClass(), BasesFound);
	int index = 0;
	while (BasesFound.IsValidIndex(index)) {
		ATurrelBasement* B = Cast<ATurrelBasement>(BasesFound[index]);
		B->ShowForMerge(TType, rang);
		index++;
	}
	ATurrelBasement* A = Cast<ATurrelBasement>(ActiveBasement);
	A->Deactivate();
}
void AMain_PC::MergeChoosePressed(ATurrelExternalData* TData) {
	if (!IsValid(ActiveBasement) || !IsValid(SecondActiveBasement)) return;
	ATurrelBasement* A = Cast<ATurrelBasement> (ActiveBasement);
	ATurrelBasement* B = Cast<ATurrelBasement>(SecondActiveBasement);
	A->DestroyTurrel();
	B->SpawnNewTurrel(TData->TurrelType);
	HideMergeWidget();
	CurrentState = E_Playing;
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
	case E_InBuildWidget:
		HideBuildWidget();
		CurrentState = E_Playing;
	case E_SearchingPlaceToBuild:
		HideDarkToneWidget();
		DeactivateAll();
		CurrentState = E_InBuildWidget;
	case E_SearchingPlaceToMove:
		HideDarkToneWidget();
		DeactivateAll();
		CurrentState = E_ShowingTurrel;
	case E_SearchingPlaceToMerge:
		HideDarkToneWidget();
		DeactivateAll();
		CurrentState = E_ShowingTurrel;
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
			ShowTurrelWidget(B->TurrelType, B->TurrelData);
			ActiveBasement = NewBase;
			B->ShowActiveTurrel();
		}
		return;
	case E_SearchingPlaceToMove:
		if (ensure(A != B) && (B->TurrelType == E_Empty)) {
			CurrentState = E_ShowingTurrel;
			B->SpawnTurrel(A->TurrelType, A->TurrelData);
			ActiveBasement = NewBase;
			A->DestroyTurrel();
			HideDarkToneWidget();
			DeactivateAll();
		}
		return;
	case E_ShowingTurrel:
		if (ensure(A != B) && (B->TurrelType != E_Empty)) {
			if (B->ShowActiveTurrel()) {
				HideTurrelWidget();
				ActiveBasement = NewBase;
				ShowTurrelWidget(B->TurrelType, B->TurrelData);
				A->Deactivate();
			}
		}
		return;
	case E_SearchingPlaceToBuild:
		if (ensure(A != B) && (B->TurrelType == E_Empty)) {
			CurrentState = E_InBuildWidget;
			B->SpawnNewTurrel(TurrelShowCaseData->TurrelType);
			ActiveBasement = NewBase;
			DeactivateAll();
			HideDarkToneWidget();
			SoftCoins -= TurrelShowCaseData->BuyCost;
		}
		return;
	case E_SearchingPlaceToMerge:
		if (ensure(A != B) && B->can_merge) {
			SecondActiveBasement = B;
			ShowMergeWidget();
			DeactivateAll();
			CurrentState = E_ChoosingToMerge;
		}
		return;
	default:
		if (B->ShowActiveTurrel()) {
			HideAllWidgets();
			CurrentState = E_ShowingTurrel;
			ActiveBasement = NewBase;
			ShowTurrelWidget(B->TurrelType, B->TurrelData);
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
