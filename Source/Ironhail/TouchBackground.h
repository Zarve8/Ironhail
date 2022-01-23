#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Main_PC.h"
#include "TurrelStaticLibrary.h"
#include "TouchBackground.generated.h"


UCLASS()
class IRONHAIL_API ATouchBackground : public APawn
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Body;
	AMain_PC* PC;
public:	
	ATouchBackground();
	virtual void BeginPlay() override;
	UFUNCTION()
		void CustomOnBeginTouch(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);


};
