#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurrelStaticLibrary.h"
#include "Engine/Texture2D.h"
#include "TurrelExternalData.generated.h"


UCLASS()
class IRONHAIL_API ATurrelExternalData : public AActor
{
	GENERATED_BODY()
public:
	ATurrelExternalData();
	void SetUp(TEnumAsByte<Turel> TurrelType);
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UTexture2D* TIcon;
	
};
