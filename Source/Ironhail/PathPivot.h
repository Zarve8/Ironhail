#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathPivot.generated.h"

UCLASS()
class IRONHAIL_API APathPivot : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnyWhere)
		TArray<AActor*> PathPoints;

public:
	APathPivot() {
		PrimaryActorTick.bCanEverTick = false;
	}
	virtual bool GetPathPointByIndex(unsigned int index, FVector &NewLoc) {
		if (PathPoints.IsValidIndex(index)) {
			NewLoc = (PathPoints[index])->GetActorLocation();
			return true;
		}
		else {
			return false;
		}
	}

};
