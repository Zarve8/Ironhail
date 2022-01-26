#pragma once
#include "TouchBackground.h"
#include "UObject/ConstructorHelpers.h"
#include "TurrelBasement.h"
#include "Kismet/GameplayStatics.h"


ATouchBackground::ATouchBackground()
{
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Base(TEXT("/Game/Source/Proxy/BatlefiledProxy"));
	if (Base.Succeeded())
	{
		Body->SetStaticMesh(Base.Object);
	}
	SetRootComponent(Body);
	PrimaryActorTick.bCanEverTick = false;
	Body->OnInputTouchEnter.AddDynamic(this, &ATouchBackground::CustomOnBeginTouch);
}
void ATouchBackground::BeginPlay() {
	PC = Cast<AMain_PC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}
void  ATouchBackground::CustomOnBeginTouch(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent) {
	UE_LOG(LogTemp, Display, TEXT("Backgroung Touched"));
	PC->ScreenTouched();
}


