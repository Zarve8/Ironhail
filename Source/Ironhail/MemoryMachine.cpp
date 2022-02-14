#include "MemoryMachine.h"
#include "Kismet/GameplayStatics.h"


// ++++++++++ Constructers ++++++++++
AMemoryMachine::AMemoryMachine()
{
	PrimaryActorTick.bCanEverTick = false;

}
void AMemoryMachine::BeginPlay()
{
	Super::BeginPlay();
	
}
// ++++++++++ Turrel Internal Data Getters ++++++++++
TArray<ATurrelInternalData*> AMemoryMachine::GetAllTurrels() {
	TArray<ATurrelInternalData*> OutArray;
	if (!IsValid(PlaceSave)) goto loop_skip;
	for (int i = 0; i < basement_count; i++) {
		if (PlaceSave->TypeArray[i] != E_Empty) {
			ATurrelInternalData* New_Data = NewObject<ATurrelInternalData>();
			New_Data->level = PlaceSave->LevelArray[i];
			New_Data->rang = PlaceSave->RangArray[i];
			New_Data->TurrelType = PlaceSave->TypeArray[i];
			New_Data->BaseIndex = i + 1;
			OutArray.Add(New_Data);
		}
	}
loop_skip:
	if (!IsValid(BagSave)) return OutArray;
	int index = 0;
	while (BagSave->TypeArray.IsValidIndex(index)) {
		if (BagSave->TypeArray[index] != E_Empty) {
			ATurrelInternalData* New_Data = NewObject<ATurrelInternalData>();
			New_Data->level = PlaceSave->LevelArray[index];
			New_Data->rang = PlaceSave->RangArray[index];
			New_Data->TurrelType = PlaceSave->TypeArray[index];
			New_Data->BaseIndex = (index + 1)*(-1);
			OutArray.Add(New_Data);
		}
		index++;
	}
	return OutArray;
}
TArray<ATurrelInternalData*> AMemoryMachine::GetPlacedTurrels() {
	if(!IsValid(PlaceSave)) return TArray<ATurrelInternalData*>{};
	TArray<ATurrelInternalData*> OutArray;
	for (int i = 0; i < basement_count; i++) {
		if (PlaceSave->TypeArray[i] != E_Empty) {
			ATurrelInternalData* New_Data = NewObject<ATurrelInternalData>();
			New_Data->level = PlaceSave->LevelArray[i];
			New_Data->rang = PlaceSave->RangArray[i];
			New_Data->TurrelType = PlaceSave->TypeArray[i];
			New_Data->BaseIndex = i + 1;
			OutArray.Add(New_Data);
		}
	}
	return OutArray;
}
TArray<ATurrelInternalData*> AMemoryMachine::GetBagTurrels() {
	if (!IsValid(BagSave)) return TArray<ATurrelInternalData*>{};
	TArray<ATurrelInternalData*> OutArray;
	int index = 0;
	while (BagSave->TypeArray.IsValidIndex(index)) {
		if (BagSave->TypeArray[index] != E_Empty) {
			ATurrelInternalData* New_Data = NewObject<ATurrelInternalData>();
			New_Data->level = PlaceSave->LevelArray[index];
			New_Data->rang = PlaceSave->RangArray[index];
			New_Data->TurrelType = PlaceSave->TypeArray[index];
			New_Data->BaseIndex = (index + 1)*(-1);
			OutArray.Add(New_Data);
		}
		index++;
	}
	return OutArray;
}
ATurrelInternalData* AMemoryMachine::LoadTurrelByIndex(int TIndex) {
	return nullptr;
}
void AMemoryMachine::SaveTurrelByIndex(ATurrelInternalData* IData, int TIndex) {
	if (!IsValid(IData)) return;
	if (IData->TurrelType == E_Empty || abs(TIndex) > 100) return;
	if (TIndex < 0) {
		TIndex = (TIndex * (-1)) - 1;
		//
	}
}
void AMemoryMachine::Init() {
	USaveGame* Slot = UGameplayStatics::LoadGameFromSlot("TurrelPlaceSlot", 0);
	if (IsValid(Slot)) {
		PlaceSave = Cast<UInternalSave>(Slot);
	}
	else {
		PlaceSave = Cast<UInternalSave>(UGameplayStatics::CreateSaveGameObject(UInternalSave::StaticClass()));
		PlaceSave->InitDefault(basement_count);
	}
	Slot = UGameplayStatics::LoadGameFromSlot("TurrelBagSlot", 0);
	if (IsValid(Slot)) {
		BagSave = Cast<UInternalSave>(Slot);
	}
	else {
		BagSave = Cast<UInternalSave>(UGameplayStatics::CreateSaveGameObject(UInternalSave::StaticClass()));
	}
}
