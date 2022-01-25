#pragma once
#include "CoreMinimal.h"
#include "Turrel.h"
#include "LongArm.generated.h"


UCLASS()
class IRONHAIL_API ALongArm : public ATurrel
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = A_Hull)
		UStaticMeshComponent* Trigger;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = A_Hull)
		UStaticMeshComponent* MagShaft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = A_Hull)
		UStaticMeshComponent* Mag;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = A_Stats)
		int mag_capacity = 3;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = A_Stats)
		FRotator ShaftUpRot = FRotator(-40, 0, 0);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = A_Stats)
		float reload_time_overrided = 10;
	FRotator MagRotDelta = FRotator(0, 0, 0);
	FRotator MagStepDelta = FRotator(0, 0, 0);
	FRotator MagRot = FRotator(0, 0, 0);
	FRotator MagTargetRot = FRotator(0, 0, 0);
	FRotator TriggerRotDelta = FRotator(0, 0, 0);
	FRotator TriggerRot = FRotator(0, 0, 0);
	int BulletsLeft = 3;
public:
	ALongArm();
	virtual void OnConstruction(const FTransform & Transform) override;
	void BeginPlay() override;
	AWalker* FindEnemy() override;
	void FireToEnemy() override;
	void ProceedFire(float delta_rime) override;
	void Reload() override;
	void EndReload() override;
	void StartRotate() override;
};