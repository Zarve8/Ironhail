#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "TurrelBasement.generated.h"

UCLASS()
class IRONHAIL_API ATurrelBasement : public APawn
{
	GENERATED_BODY()

public:

	ATurrelBasement();

protected:
	UPROPERTY(EditAnywhere, Category = A_Body)
		UStaticMeshComponent* Body;
	UPROPERTY(EditAnywhere, Category = A_Body)
		UPaperSpriteComponent* DistanceSprite;
	virtual void BeginPlay() override;
public:	
	virtual void OnConstruction(const FTransform & Transform) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
		void CustomOnBeginTouch(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
		void CustomOnEndTouch(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

};
