#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStaticsTypes.h"
#include "ParticleDefinitions.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

void PlaceParticleLine(FVector BaseLoc, FVector TargetLoc, UParticleSystem* Particle, AActor* Owner) {
	FRotator R = (TargetLoc - BaseLoc).Rotation();
	UParticleSystemComponent* j = UGameplayStatics::SpawnEmitterAtLocation(Owner->GetWorld(), Particle, BaseLoc, R, true);
}