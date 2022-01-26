#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "TurrelExternalData.h"
#include "TurrelStaticLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "TurrelClassFinder.h"
#include "Engine.h"
#include "MenuStateEnum.h"
#include "Main_PC.generated.h"


UCLASS()
class IRONHAIL_API AMain_PC : public APlayerController
{
	GENERATED_BODY()
	//Widget Classes:
protected:
	TSubclassOf<UUserWidget> MenuBarClass;
	UUserWidget* MenuBar = nullptr;
	TSubclassOf<UUserWidget> TurrelShowCaseClass;
	UUserWidget* TurrelShowCase = nullptr;
	TSubclassOf<UUserWidget> MenuBuildClass;
	UUserWidget* MenuBuildWidget = nullptr;
	//External Data for Widgets:
public:
	ATurrelExternalData* ExternalDataFabric(TEnumAsByte<Turel> TurrelType);
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		ATurrelExternalData* TurrelShowCaseData = nullptr; //Also used for building
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		TArray<ATurrelExternalData*> BuildArrayData;
	//Function to show Widgets:
protected:
	void HideAllWidgets();
		void CreateMenuBar();
		void ShowTurrelWidget(TEnumAsByte<Turel> TurrelType, int level);
		void HideTurrelWidget();
		void ShowMissionsWidget();
		void ShowPowerUpsWidget();
		void ShowBuildWidget();
		void HideBuildWidget();
	//Functions called in widgets
public:
	UFUNCTION(BlueprintCallable)
		void BuildButtonPressed();
	UFUNCTION(BlueprintCallable)
		void BuyPressed(ATurrelExternalData* Data);
	UFUNCTION(BlueprintCallable)
		void MissionButtonPressed();
	UFUNCTION(BlueprintCallable)
		void PowerUpButtonPressed();
	UFUNCTION(BlueprintCallable)
		void MovePressed();
	UFUNCTION(BlueprintCallable)
		void SellPressed();
	//Functions called from Basement
public:
	void ScreenTouched();
	void TurrelTouched(AActor* NewBase);
	//State Actions/Variables
protected:
	void SetAllForPlacement();
	void DeactivateAll();
	//Constructers
public:
	AMain_PC();
	void BeginPlay() override;
	void Tick(float DealtaTime) override;
public:
	AActor* ActiveBasement = nullptr;
	ATurrelClassFinder* TFinder = nullptr;
	TEnumAsByte<MenuState> CurrentState = E_Playing;
	UPROPERTY(BlueprintReadOnly)
		int SoftCoins = 10000;
	UPROPERTY(BlueprintReadOnly)
		int HardCoins = 10000;
};
