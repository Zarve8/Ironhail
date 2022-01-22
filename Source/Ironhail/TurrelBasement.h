#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TurrelBasement.generated.h"

UCLASS()
class IRONHAIL_API ATurrelBasement : public APawn
{
	GENERATED_BODY()

public:

	ATurrelBasement();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
