#include "TurrelExternalData.h"
#include "UObject/ConstructorHelpers.h"

ATurrelExternalData::ATurrelExternalData(){
	static ConstructorHelpers::FObjectFinder<UTexture2D> TurrelIcon(TEXT("/Game/Source/HUD/TurrelIcons/ChipCoin"));
	if (TurrelIcon.Succeeded()) {
		TIcon = TurrelIcon.Object;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Texture Icon Not found"));
	}
	PrimaryActorTick.bCanEverTick = true;
}
void ATurrelExternalData::SetUp(TEnumAsByte<Turel> TurrelType) {

}