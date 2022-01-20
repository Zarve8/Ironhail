#pragma once
#include "CoreMinimal.h"
#include "Turrel.h"
#include "Laser.generated.h"


UCLASS()
class IRONHAIL_API ALaser : public ATurrel
{
	GENERATED_BODY()
public:
	ALaser();
protected:
	void FollowTarget();
public:
	void BeginPlay() override;
	AWalker* FindEnemy() override;
	void FireToEnemy() override;
	void ProceedFire(float delta_time) override;
};
