#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "TurrelExternalData.h"
#include "TurrelStaticLibrary.h"
#include "Main_PC.generated.h"


UCLASS()
class IRONHAIL_API AMain_PC : public APlayerController
{
	GENERATED_BODY()
	//Widget Classes:
protected:
	TSubclassOf<UUserWidget> TurrelShowCaseClass;
	UUserWidget* TurrelShowCase = nullptr;
	TSubclassOf<UUserWidget> MenuBuildClass;
	UUserWidget* MenuBuild = nullptr;

	//External DAta for Widgets:
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		ATurrelExternalData* TurrelShowCaseData = nullptr;
	//Function to show Widgets:
public:
	UFUNCTION(BlueprintCallable)
		void ShowTurrelWidget(TEnumAsByte<Turel> TurrelType, int level);
	UFUNCTION(BlueprintCallable)
		void HideTurrelWidget();
	UFUNCTION(BlueprintCallable)
		void ShowMissionsWidget();
	UFUNCTION(BlueprintCallable)
		void HideMissionsWidget();
	UFUNCTION(BlueprintCallable)
		void ShowPowerUpsWidget();
	UFUNCTION(BlueprintCallable)
		void HidePowerUpsWidget();
	UFUNCTION(BlueprintCallable)
		void ShowBuildWidget();
	UFUNCTION(BlueprintCallable)
		void HideBuildWidget();

public:
	AMain_PC();
	void BeginPlay() override;
	void Tick(float DealtaTime) override;
	
};
