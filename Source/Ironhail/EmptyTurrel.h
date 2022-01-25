#pragma once
#include "CoreMinimal.h"
#include "Turrel.h"
#include "EmptyTurrel.generated.h"


UCLASS()
class IRONHAIL_API AEmptyTurrel : public ATurrel
{
	GENERATED_BODY()
public:
	AEmptyTurrel();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

};
