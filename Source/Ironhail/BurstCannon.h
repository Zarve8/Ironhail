#pragma once
#include "CoreMinimal.h"
#include "Turrel.h"
#include "BurstCannon.generated.h"


UCLASS()
class IRONHAIL_API ABurstCannon : public ATurrel
{
	GENERATED_BODY()
public:
	ABurstCannon();
protected:
	UPROPERTY(EditAnywhere, Category = A_Hull)
		UStaticMeshComponent* Gatling;
	UPROPERTY(EditAnywhere, Category = A_Hull)
		int MuzzlesCount = 5;
	FRotator GatlingRotator = FRotator(0, 0, 0);
	float GatlingSpeedRotator = 0;
	float RotateAngle = 0;
	float GatlingTargetRotate = 0;
public:
	void OnConstruction(const FTransform & Transform) override;
	void BeginPlay() override;
	AWalker* FindEnemy() override;
	virtual void FireToEnemy() override;
	virtual void ProceedFire(float delta_seconds) override;
};
