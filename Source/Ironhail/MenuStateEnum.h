#pragma once
#include "CoreMinimal.h"
#include "MenuStateEnum.generated.h"


UENUM(BlueprintType, Category = MenuStates)
enum MenuState {
	E_Playing UMETA(DisplayName = "Playing"),
	E_InBuildWidget UMETA(DisplayName = "InBuildWidget"),
	E_SearchingPlaceToBuild UMETA(DisplayName = "SearchingPlaceToBuild"),
	E_ShowingTurrel UMETA(DisplayName = "ShowingTurrel"),
	E_SearchingPlaceToMove UMETA(DisplayName = "SearchingPlaceToMove"),
	E_SearchingPlaceToMerge UMETA(DisplayName = "SearchingPlaceToMerge"),
	E_ChoosingToMerge UMETA(DisplayName = "ChoosingToMerge")
};

/*

void PrintMenuState(TEnumAsByte<MenuState> State) {
	switch (State) {
	case E_InBuildWidget:
		UE_LOG(LogTemp, Error, TEXT("Display State: InBuildWidget"));
		return;
	case E_Playing:
		UE_LOG(LogTemp, Error, TEXT("Display State: Playing"));
		return;
	case E_SearchingPlaceToBuild:
		UE_LOG(LogTemp, Error, TEXT("Display State: SearchingPlaceToBuild"));
		return;
	case E_SearchingPlaceToMerge:
		UE_LOG(LogTemp, Error, TEXT("Display State: SearchingPlaceToMerge"));
		return;
	case E_SearchingPlaceToMove:
		UE_LOG(LogTemp, Error, TEXT("Display State: SearchingPlaceToMove"));
		return;
	case E_ShowingTurrel:
		UE_LOG(LogTemp, Error, TEXT("Display State: ShowingTurrel"));
		return;
	case E_ChoosingToMerge:
		UE_LOG(LogTemp, Error, TEXT("Display State: ChoosingToMerge"));
		return;
	default:
		UE_LOG(LogTemp, Error, TEXT("Display State: Default"));
		return;
	}
}

*/