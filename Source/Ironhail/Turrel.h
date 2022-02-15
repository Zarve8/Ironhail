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
#include "SkillLibrary.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Turrel.generated.h"

UCLASS()
class IRONHAIL_API ATurrel : public AActor, public IActionMachine, public ITurrelParticleHelper
{
	GENERATED_BODY()
	//Constructors
public:	
	ATurrel();
	virtual void OnConstruction(const FTransform & Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	//Function for ActionMachine
public:
	virtual Action_AM* GetBaseAction() override;
	virtual AWalker* FindEnemy() { return nullptr; UE_LOG(LogTemp, Error, TEXT("FindEnemy not overrided")); }
	virtual float CalculateRotateTime();
	virtual void StartRotate();
	virtual void ProceedRotate(float delta_seconds) {}
	virtual void FireToEnemy() {}
	virtual void ProceedFire(float delta_seconds) {}
	virtual void Reload() {}
	virtual void ProceedReload(float delta_seconds) {}
	virtual void EndReload() {}
	//Finding enemy
protected:
	AWalker* FindAnyEnemy();
	AWalker* FindNearestEnemy();
	AWalker* FindToughestEnemy();
	AWalker* FindWeakestEnemy();
	//Body
protected:
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
	//Local variables
public:
	AWalker* PreferedEnemy = nullptr;
protected:
	FVector BaseLoc = FVector(0, 0, 0);
	FRotator Target_Rotation = FRotator(0, 0, 0);
	//Stats
public:	
	UPROPERTY(EditAnywhere, Category = A_Stats) //Shoot stats
		float reload_time = 10;
	UPROPERTY(EditAnywhere, Category = A_Stats)
		float shoot_time = 10;
	UPROPERTY(EditAnywhere, Category = A_Stats)
		float fire_distance = 10000;
	UPROPERTY(EditAnywhere, Category = A_Stats)
		float damage = 10;
	float bullet_speed_cof = 1;
	UPROPERTY(EditAnywhere, Category = A_Stats) //Freeze stats
		bool is_freeze = false;
	UPROPERTY(EditAnywhere, Category = A_Stats)
		float freeze_time = 0;
	UPROPERTY(EditAnywhere, Category = A_Stats) //Lightning stats
		bool is_lightning = false;
	UPROPERTY(EditAnywhere, Category = A_Stats)
		int lightning_count = 0;
	UPROPERTY(EditAnywhere, Category = A_Stats)
		float lightning_damage = 10;
	UPROPERTY(EditAnywhere, Category = A_Stats) //Burn stats
		bool is_burn = false;
	UPROPERTY(EditAnywhere, Category = A_Stats)
		float burning_time = 0;
	UPROPERTY(EditAnywhere, Category = A_Stats)
		float burning_damage = 10;
	//Base Stats
public:
	float base_reload_time = 10;
	float base_shoot_time = 10;
	float base_fire_distance = 10000;
	float base_damage = 10;
	bool base_is_freeze = false;
	float base_freeze_time = 0;
	bool base_is_lightning = false;
	int base_lightning_count = 0;
	float base_lightning_damage = 0;
	bool base_is_burn = false;
	float base_burning_time = 0;
	float base_burning_damage = 0;
	//Modifiers and Skills
public:
	UPROPERTY(EditAnywhere)
		TEnumAsByte<Mod> SelfMod = E_NoneMod;
	void BackUp_Stats();
	void Reset_Mod();
	void Apply_Mod(TEnumAsByte<Mod> NMod);
	void Apply_Array_Mod(TArray<TEnumAsByte<Mod>> NArray);
	//Modifier Constants
public:
	const float additive_freeze_time = 0.5;
	const float additive_burn_time = 0.33;
};

class Reload_AM : public Action_AM {
	ATurrel* Owner;
public:
	Reload_AM(ATurrel* Owner) : Owner(Owner) {
		seconds_left = Owner->reload_time;
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
	}
	virtual void Start() {
		Owner->StartRotate();
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
	}
	virtual Action_AM* Next() {
		if (IsValid(Owner->PreferedEnemy)) {
			return new Rotate_AM(Owner);
		}
		return new Delay_AM();
	}
};
