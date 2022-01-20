#pragma once
#include "CoreMinimal.h"
#include "Turrel.h"
#include "FrostCannon.generated.h"


UCLASS()
class IRONHAIL_API AFrostCannon : public ATurrel
{
	GENERATED_BODY()
public:
	AFrostCannon();
protected:
	UPROPERTY(EditAnywhere, Category = A_Hull)
		UStaticMeshComponent* Beam;
	UPROPERTY(EditAnywhere, Category = A_Hull)
		FName Fire_Socket_Name = TEXT("F_5");
public:
	void OnConstruction(const FTransform & Transform) override;
	AWalker* FindEnemy() override;
	void FireToEnemy() override;
	void StartRotate() override;
};
