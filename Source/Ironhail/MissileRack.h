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
public:
	AWalker* FindEnemy() override;
	void FireToEnemy() override;
	
};
