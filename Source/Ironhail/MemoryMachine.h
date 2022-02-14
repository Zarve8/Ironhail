#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurrelStaticLibrary.h"
#include "TurrelInternalData.h"
#include "InternalSave.h"
#include "MemoryMachine.generated.h"

UCLASS()
class IRONHAIL_API AMemoryMachine : public AActor
{
	GENERATED_BODY()
	// Constructers
public:	
	AMemoryMachine();
	void BeginPlay() override;
	void Init();
	// Turrel Internal Data Getters
public:
	TArray<ATurrelInternalData*> GetAllTurrels();
	TArray<ATurrelInternalData*> GetPlacedTurrels();
	TArray<ATurrelInternalData*> GetBagTurrels();
	ATurrelInternalData* LoadTurrelByIndex(int TIndex);
	void SaveTurrelByIndex(ATurrelInternalData* IData, int TIndex);
	UInternalSave* PlaceSave = nullptr;
	UInternalSave* BagSave = nullptr;
	// Constants
private:
	const int basement_count = 5;
};
