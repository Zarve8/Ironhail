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
	//Constants Merging
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<TEnumAsByte<Turel>> ChildTurrels;
	//Constants Buy
public:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
		TEnumAsByte<Turel> TurrelType = E_Empty;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		int BuyCost = 100;
	//Showcase Images/Text
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UTexture2D* TIcon;
	//Constructer
public:
	ATurrelExternalData() {
		PrimaryActorTick.bCanEverTick = true;
	}
};

