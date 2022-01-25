#pragma once
#include "CoreMinimal.h"
#include "ActionMachine.h"
#include "Walker.h"
#include "GameFramework/Actor.h"
#include "TurrelParticleHelper.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStaticsTypes.h"
#include "ParticleDefinitions.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Turrel.generated.h"

UCLASS()
class IRONHAIL_API ATurrel : public AActor, public IActionMachine, public ITurrelParticleHelper
{
	GENERATED_BODY()
public:	
	ATurrel();

protected:
	virtual void BeginPlay() override;
	FVector BaseLoc = FVector(0, 0, 0);
	FRotator Target_Rotation = FRotator(0, 0, 0);
	AWalker* FindAnyEnemy();
	AWalker* FindNearestEnemy();
	AWalker* FindToughestEnemy();
	AWalker* FindWeakestEnemy();
	UPROPERTY(EditAnywhere, Category = A_Bath)
		FVector Head_Scale = FVector(1, 1, 1);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = A_Hull)
		UStaticMeshComponent* Body = nullptr;
	UPROPERTY(EditAnywhere, Category = A_Hull)
		UStaticMeshComponent* Head = nullptr;
	UPROPERTY(EditAnywhere, Category = A_Bath)
		UParticleSystem* Fire_Particle;
	FName Head_Socket_Name = TEXT("Head_Socket");
	FName Head_Face_Socket_Name = TEXT("Face_Socket");

public:	
	AWalker* PreferedEnemy = nullptr;
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform & Transform) override;
	virtual Action_AM* GetBaseAction() override;
	virtual AWalker* FindEnemy() {return nullptr; UE_LOG(LogTemp, Error, TEXT("FindEnemy not overrided"));}
	virtual float CalculateRotateTime();
	virtual void StartRotate();
	virtual void ProceedRotate(float delta_seconds) {}
	virtual void FireToEnemy() {}
	virtual void ProceedFire(float delta_seconds) {}
	virtual void Reload() {}
	virtual void ProceedReload(float delta_seconds) {}
	virtual void EndReload() {}
	UPROPERTY(EditAnywhere, Category = A_Stats)
		float reload_time = 10;
	UPROPERTY(EditAnywhere, Category = A_Stats)
		float shoot_time = 10;
	UPROPERTY(EditAnywhere, Category = A_Stats)
		float fire_distance = 100;
};


class Reload_AM : public Action_AM {
	ATurrel* Owner;
public:
	Reload_AM(ATurrel* Owner) : Owner(Owner) {
		seconds_left = Owner->reload_time;
		//UE_LOG(LogTemp, Error, TEXT("Start Reload"));
	}
	virtual void Start() override {
		Owner->Reload();
	}
	virtual void Proceed(float delta_seconds) {
		Owner->ProceedReload(delta_seconds);
	}
	virtual Action_AM* Next() {
		return nullptr;
	}
};

class Fire_AM : public Action_AM {
	ATurrel* Owner;
public:
	Fire_AM(ATurrel* Owner) : Owner(Owner) {
		seconds_left = Owner->shoot_time;
	}
	virtual void Start() override {
		Owner->FireToEnemy();
		//UE_LOG(LogTemp, Error, TEXT("Start Fire"));
	}
	virtual void Proceed(float delta_seconds) {
		Owner->ProceedFire(delta_seconds);
	}
	virtual Action_AM* Next() {
		return new Reload_AM(Owner);
	}
};

class Rotate_AM : public Action_AM {
	ATurrel* Owner;
public:
	Rotate_AM(ATurrel* Owner) : Owner(Owner) {
		seconds_left = Owner->CalculateRotateTime();
		//UE_LOG(LogTemp, Error, TEXT("Calculating Rotate"));
	}
	virtual void Start() {
		Owner->StartRotate();
		//UE_LOG(LogTemp, Error, TEXT("Rotating"));
	}
	virtual void Proceed(float delta_seconds) {
		Owner->ProceedRotate(delta_seconds);
	}
	virtual Action_AM* Next() {
		Owner->EndReload();
		if (IsValid(Owner->PreferedEnemy)) {
			return new Fire_AM(Owner);
		}
		return nullptr;
	}
};

class Search_AM : public Action_AM {
	ATurrel* Owner;
public:
	Search_AM(ATurrel* Owner) : Owner(Owner) {
		seconds_left = 0.01;
	}
	virtual void Start() override {
		Owner->PreferedEnemy = Owner->FindEnemy();
		//UE_LOG(LogTemp, Error, TEXT("Find Enemy"));
	}
	virtual Action_AM* Next() {
		if (IsValid(Owner->PreferedEnemy)) {
			return new Rotate_AM(Owner);
		}
		return new Delay_AM();
	}
};
