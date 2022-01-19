#pragma once
#include "MissileRack.h"
#include "MyParticleHelper.h"


AWalker* AMissileRack::FindEnemy() {
	UE_LOG(LogTemp, Error, TEXT("Missle Finding TSart"));
	return this->FindAnyEnemy();
}
//TODO redo with multiple shots
void AMissileRack::FireToEnemy() {
	
	if (IsValid(Fire_Particle)&&IsValid(PreferedEnemy)) {
		if (Fire_Socket_Names.IsValidIndex(0)) {
			FVector F_Loc = Head->GetSocketLocation(Fire_Socket_Names[0]);
			FVector Enemy_Loc = PreferedEnemy->GetActorLocation();
			PlaceParticleLine(F_Loc, Enemy_Loc, Fire_Particle, this);
		}
	}
}

