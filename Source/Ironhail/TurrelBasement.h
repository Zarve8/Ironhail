#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "TurrelStaticLibrary.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Main_PC.h"
#include "TurrelClassFinder.h"
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
	int level = 1;
	void SpawnTurrel(TEnumAsByte<Turel> Type);
	void DestroyTurrel();
	TEnumAsByte<Turel> TurrelType = E_Empty;
	ATurrel* ChildTurrel = nullptr;
	//Show Actions
public:
	bool ShowForPlacement();
	bool ShowActiveTurrel();
	void Deactivate();
};
