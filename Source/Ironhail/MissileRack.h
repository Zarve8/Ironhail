#pragma once
#include "CoreMinimal.h"
#include "Turrel.h"
#include "MissileRack.generated.h"


UCLASS()
class IRONHAIL_API AMissileRack : public ATurrel
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = A_Hull)
		TArray<FName> Fire_Socket_Names;
	int missile_capacity = 2;
	int fire_index = -1;
public:
	AWalker* FindEnemy() override;
	void BeginPlay() override;
	void FireToEnemy() override;
	void FireNext();
};
