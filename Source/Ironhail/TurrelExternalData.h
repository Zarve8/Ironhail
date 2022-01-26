#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurrelStaticLibrary.h"
#include "Engine/Texture2D.h"
#include "UObject/ConstructorHelpers.h"
#include "TurrelExternalData.generated.h"


UCLASS()
class IRONHAIL_API ATurrelExternalData : public AActor
{
	GENERATED_BODY()
	//Constants
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UTexture2D* TIcon;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int BuyCost = 100;
	TEnumAsByte<Turel> TurrelType = E_AutoCannon_5;
public:
	ATurrelExternalData() {
		static ConstructorHelpers::FObjectFinder<UTexture2D> TurrelIcon(TEXT("/Game/Source/HUD/TurrelIcons/ChipCoin"));
		if (TurrelIcon.Succeeded()) {
			TIcon = TurrelIcon.Object;
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("Texture Icon Not found"));
		}
		PrimaryActorTick.bCanEverTick = true;
	}
};

UCLASS()
class IRONHAIL_API AProxyData_ED : public ATurrelExternalData {
	GENERATED_BODY()
public:
	AProxyData_ED() : ATurrelExternalData() {

	}
};