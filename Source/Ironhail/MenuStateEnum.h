#pragma once
#include "CoreMinimal.h"
#include "MenuStateEnum.generated.h"


UENUM(BlueprintType, Category = MenuStates)
enum MenuState {
	E_Playing UMETA(DisplayName = "Playing"),
	E_InBuildWidget UMETA(DisplayName = "InBuildWidget"),
	E_SearchingPlaceToBuild UMETA(DisplayName = "SearchingPlaceToBuild"),
	E_ShowingTurrel UMETA(DisplayName = "ShowingTurrel"),
	E_SearchingPlaceToMove UMETA(DisplayName = "SearchingPlaceToMove")
};

