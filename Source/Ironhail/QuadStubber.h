#pragma once
#include "CoreMinimal.h"
#include "Turrel.h"
#include "QuadStubber.generated.h"


UCLASS()
class IRONHAIL_API AQuadStubber : public ATurrel
{
	GENERATED_BODY()
public:
	AQuadStubber();
protected:
	UPROPERTY(EditAnywhere, Category = A_Hull)
		UStaticMeshComponent* Muzzle_1;
	UPROPERTY(EditAnywhere, Category = A_Hull)
		UStaticMeshComponent* Muzzle_2;
	UPROPERTY(EditAnywhere, Category = A_Hull)
		UStaticMeshComponent* Muzzle_3;
	UPROPERTY(EditAnywhere, Category = A_Hull)
		UStaticMeshComponent* Muzzle_4;
	UPROPERTY(EditAnywhere, Category = A_Hull)
		UStaticMeshComponent* Mag_1;
	UPROPERTY(EditAnywhere, Category = A_Hull)
		UStaticMeshComponent* Mag_2;
	UPROPERTY(EditAnywhere, Category = A_Hull)
		UStaticMeshComponent* Mag_3;
	UPROPERTY(EditAnywhere, Category = A_Hull)
		UStaticMeshComponent* Mag_4;
	bool is_1 = true;
	bool is_2 = true;
	UStaticMeshComponent* ActiveMuzzle = nullptr;
	UPROPERTY(EditAnywhere, Category = A_Stats)
		float ShiftSteps = 2;
	UPROPERTY(EditAnywhere, Category = A_Stats)
		float ShiftDepth = 50;
	UPROPERTY(EditAnywhere, Category = A_Stats)
		float MagRotationSpeed = 60;
	FVector ActiveMuzzleLoc;
	FVector DShift = FVector(0, 0, 0);
	float ShiftDelay = 1;
	float time_left = 0.1;
	FRotator MagRotator = FRotator(0, 0, 0);
	void RotateMag(float delta_time);
public:
	AWalker* FindEnemy() override;
	virtual void OnConstruction(const FTransform & Transform) override;
	virtual void BeginPlay() override;
	virtual void FireToEnemy() override;
	virtual void ProceedFire(float delta_seconds) override;
	virtual void Reload() override;
	virtual void ProceedReload(float delta_seconds) override;
	
};
