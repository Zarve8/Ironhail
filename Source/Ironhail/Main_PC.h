#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "TurrelExternalData.h"
#include "TurrelStaticLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"
#include "Main_PC.generated.h"


UCLASS()
class IRONHAIL_API AMain_PC : public APlayerController
{
	GENERATED_BODY()
protected:
	AActor* ActiveBasement = nullptr;
	//Widget Classes:
protected:
	TSubclassOf<UUserWidget> MenuBarClass;
	UUserWidget* MenuBar = nullptr;
	TSubclassOf<UUserWidget> TurrelShowCaseClass;
	UUserWidget* TurrelShowCase = nullptr;
	TSubclassOf<UUserWidget> MenuBuildClass;
	UUserWidget* MenuBuild = nullptr;
	//External DAta for Widgets:
public:
	ATurrelExternalData* ExternalDataFabric(TEnumAsByte<Turel> TurrelType);
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		ATurrelExternalData* TurrelShowCaseData = nullptr;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		TArray<ATurrelExternalData*> BuildArrayData;
	//Function to show Widgets:
public:
	UFUNCTION(BlueprintCallable)
		void CreateMenuBar();
	UFUNCTION(BlueprintCallable)
		void ShowTurrelWidget(TEnumAsByte<Turel> TurrelType, int level);
	UFUNCTION(BlueprintCallable)
		void ShowMissionsWidget();
	UFUNCTION(BlueprintCallable)
		void ShowPowerUpsWidget();
	UFUNCTION(BlueprintCallable)
		void ShowBuildWidget();
	AActor* ScreenTouched();
	void SetActiveBasement(AActor* NewActive);
public:
	AMain_PC();
	void BeginPlay() override;
	void Tick(float DealtaTime) override;
	
};
