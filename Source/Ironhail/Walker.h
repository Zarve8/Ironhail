#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathPivot.h"
#include "ActionMachine.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Walker.generated.h"

UCLASS()
class IRONHAIL_API AWalker : public AActor, public IActionMachine
{
	GENERATED_BODY()
	
public:	
	AWalker();

protected:
	virtual void BeginPlay() override;
	virtual void Die();
	virtual Action_AM* GetBaseAction() override;
	UPROPERTY(EditAnywhere, Category = A_Hull)
		USkeletalMeshComponent* Body = nullptr;
public:	
	APathPivot* path = nullptr;
	int PathIndex = 0;
	virtual void Tick(float DeltaTime) override;
	virtual void SufferDamage(float damage);
	void RotateToDirection(FVector Forward);
	UPROPERTY(EditAnywhere, Category = A_Stats)
		float health = 0.5;
	UPROPERTY(EditAnywhere, Category = A_Stats)
		float speed = 150;
	UPROPERTY(EditAnywhere, Category = A_Stats)
		float armour_cof = 1;
	UPROPERTY(EditAnyWhere, Category = A_Stat)
		float ParallelShift = 25;

};

class FollowPath_AM : public Action_AM {
	AWalker* Owner;
	FVector VForward;
	FVector Loc;
public:
	FollowPath_AM(AWalker* Owner){
		this->Owner = Owner;
		FVector TargetLoc;
		FVector NextPoint;
		FVector LastPoint;
		FVector CurPoint;
		Loc = Owner->GetActorLocation();
		Owner->PathIndex += 1;
		if (Owner->path->GetPathPointByIndex(Owner->PathIndex, CurPoint) && Owner->path->GetPathPointByIndex(Owner->PathIndex + 1, NextPoint)) {
			Owner->path->GetPathPointByIndex(Owner->PathIndex - 1, LastPoint);
			FVector L = CurPoint - LastPoint;
			FVector N = CurPoint - NextPoint;
			L.Normalize();
			N.Normalize();
			FVector H = (L + N);
			H.Normalize();
			TargetLoc = CurPoint + H * Owner->ParallelShift;
			seconds_left = FVector::Distance(TargetLoc, Loc) / Owner->speed;
			VForward = L * Owner->speed;
			Owner->RotateToDirection(VForward);
		}
		//TODO set gameover;
		else {
			UE_LOG(LogTemp, Warning, TEXT("Reached end of path"));
			Owner->Destroy();
		}
	}

	void Start() override {}

	void Proceed(float delta_seconds) override {
		Loc += delta_seconds * VForward;
		Owner->SetActorLocation(Loc, true);
	}

	Action_AM* Next() override {
		return new FollowPath_AM(Owner);
	}
};


class DelayBeforeMove_AM : public Delay_AM {
	AWalker* Owner;
public:
	DelayBeforeMove_AM(AWalker* Owner, float delay): Owner(Owner){
		this->seconds_left = delay;
	}
	Action_AM* Next() override {
		return new FollowPath_AM(Owner);
	}
};