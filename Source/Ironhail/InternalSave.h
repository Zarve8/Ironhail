#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TurrelStaticLibrary.h"
#include "InternalSave.generated.h"


UCLASS()
class IRONHAIL_API UInternalSave : public USaveGame
{
	GENERATED_BODY()
	//Functions
public:
	void InitDefault(int range) {
		for (int i = 0; i < range; i++) {
			LevelArray.Add(-1);
			RangArray.Add(-1);
			TypeArray.Add(E_Empty);
		}
	}
	//Data
public:
	UPROPERTY()
		TArray<int32> LevelArray = {};
	UPROPERTY()
		TArray<int32> RangArray = {};
	UPROPERTY()
		TArray<TEnumAsByte<Turel>> TypeArray = {};
};
