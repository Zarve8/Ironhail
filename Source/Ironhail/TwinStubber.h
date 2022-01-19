#pragma once
#include "CoreMinimal.h"
#include "Turrel.h"
#include "TwinStubber.generated.h"


UCLASS()
class IRONHAIL_API ATwinStubber : public ATurrel
{
	GENERATED_BODY()
public:
	ATwinStubber();
protected:
	UPROPERTY(EditAnywhere, Category = A_Hull)
		UStaticMeshComponent* LeftMuzzle;
	UPROPERTY(EditAnywhere, Category = A_Hull)
		UStaticMeshComponent* RightMuzzle;
	bool isleft = true;
	UStaticMeshComponent* ActiveMuzzle = nullptr;
	UPROPERTY(EditAnywhere, Category = A_Hull)
		FName Fire_Socket_Name = TEXT("F_1");
	UPROPERTY(EditAnywhere, Category = A_Hull)
		FName Left_Muzzle_Socket_Name = TEXT("M_1");
	UPROPERTY(EditAnywhere, Category = A_Hull)
		FName Right_Muzzle_Socket_Name = TEXT("M_2");
public:
	AWalker* FindEnemy() override;
	virtual void OnConstruction(const FTransform & Transform) override;
	virtual void FireToEnemy() override;
	virtual void ProceedFire(float delta_seconds) override;
	virtual void StartRotate() override;
};
