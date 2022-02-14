#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurrelStaticLibrary.h"
#include "TurrelInternalData.generated.h"


UCLASS()
class IRONHAIL_API ATurrelInternalData : public AActor
{
	GENERATED_BODY()
	//Turrel Type
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		   TEnumAsByte<Turel> TurrelType = E_AutoCannon_1;
	//TODO : set rang and level
	UFUNCTION(BlueprintCallable)
		void SetUpByType(TEnumAsByte<Turel> TType)
	{
		this->TurrelType = TType;
	}
	//Level
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int level = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int max_level = 10;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int rang = 1;
	//Index for memory load/reload
public:
		int BaseIndex = -200;
	//Proxy Upgrading
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int upgrade_cost = 10;
	UFUNCTION(BlueprintCallable)
		bool Upgrade() //returns next upgrade cost
	{
		if (level < max_level) {
			level += 1;
			upgrade_cost *= 1.2;
			return true;
		}
		return false;
	}
	

};
