#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "TurrelStaticLibrary.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Main_PC.h"
#include "TurrelClassFinder.h"
#include "TurrelInternalData.h"
#include "SkillLibrary.h"
#include "TurrelBasement.generated.h"

UCLASS()
class IRONHAIL_API ATurrelBasement : public APawn
{
	GENERATED_BODY()
	//Proxy
public:
	UPROPERTY(EditAnywhere, Category = AA_Proxy)
		TEnumAsByte<Turel> Init_Type = E_Empty;
	//Body
protected:
	UPROPERTY(EditAnywhere, Category = A_Body)
		UStaticMeshComponent* Body;
	UPROPERTY(EditAnywhere, Category = A_Body)
		UPaperSpriteComponent* DistanceSprite;
	UPROPERTY(EditAnywhere, Category = A_Body)
		UPaperSpriteComponent* PlacementSprite;
	//External classes
public:
	AMain_PC* PC;
	//Constructors
public:	
	ATurrelBasement();
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform & Transform) override;
	//Inputs
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
		void CustomOnBeginTouch(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
		void CustomOnEndTouch(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
	//Turrel Actions/Prperties
public:
	ATurrelInternalData* TurrelData = nullptr;
	void SpawnEmpty();
	void SpawnTurrel(TEnumAsByte<Turel> Type, ATurrelInternalData* NewData);
	void SpawnNewTurrel(TEnumAsByte<Turel> Type);
	void DestroyTurrel();
	TEnumAsByte<Turel> TurrelType = E_Empty;
	ATurrel* ChildTurrel = nullptr;
	//Show Actions
public:
	bool ShowForPlacement();
	bool ShowActiveTurrel();
	void ShowForMerge(TEnumAsByte<Turel> TType, int rang);
	void Deactivate();
	//Additional variables
	bool can_merge = false;
	//Modifiers Functions
public:
	TArray<TEnumAsByte<Mod>> Given_Mods;
	TArray<ATurrelBasement*> Connected_Basements;
	void Get_Mod(TEnumAsByte<Mod> NMod);
	void Give_Mod();
	void Remove_Mod(TEnumAsByte<Mod> RMod);

};
