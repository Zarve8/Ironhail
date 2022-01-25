#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turrel.h"
#include "TurrelStaticLibrary.h"
#include "TurrelClassFinder.generated.h"


UCLASS()
class IRONHAIL_API ATurrelClassFinder : public AActor
{
	GENERATED_BODY()
	//Turrel Classes ref
private:
	TSubclassOf<ATurrel> Empty;
	TSubclassOf<ATurrel> AutoCannon_2;
	TSubclassOf<ATurrel> AutoCannon_3;
	TSubclassOf<ATurrel> AutoCannon_4;
	TSubclassOf<ATurrel> AutoCannon_5;
	TSubclassOf<ATurrel> AutoCannon_6;
	TSubclassOf<ATurrel> RocketPod_4;
	TSubclassOf<ATurrel> RocketPod_5;
	TSubclassOf<ATurrel> RocketPod_6;
	TSubclassOf<ATurrel> LongArm_3;
	TSubclassOf<ATurrel> LongArm_4;
	TSubclassOf<ATurrel> LongArm_5;
	TSubclassOf<ATurrel> LongArm_6;
	TSubclassOf<ATurrel> FrostCannon_5;
	TSubclassOf<ATurrel> FrostCannon_6;
	TSubclassOf<ATurrel> Laser_5;
	TSubclassOf<ATurrel> Laser_6;
public:
	ATurrelClassFinder();
	TSubclassOf<ATurrel> GetTurrelClassByEnum(TEnumAsByte<Turel> Type);
};
