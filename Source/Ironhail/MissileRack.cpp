#pragma once
#include "MissileRack.h"


AWalker* AMissileRack::FindEnemy() {
	return this->FindAnyEnemy();
}
//TODO redo with multiple shots
void AMissileRack::FireToEnemy() {
	FireNext();
}
void AMissileRack::BeginPlay() {
	missile_capacity = Fire_Socket_Names.GetAllocatedSize();
	ATurrel::BeginPlay();
}
void  AMissileRack::FireNext() {
	fire_index += 1;
	fire_index %= missile_capacity;
	if (IsValid(Fire_Particle) && IsValid(PreferedEnemy)) {
		if (Fire_Socket_Names.IsValidIndex(fire_index)) {
			FVector F_Loc = Head->GetSocketLocation(Fire_Socket_Names[fire_index]);
			FVector Enemy_Loc = PreferedEnemy->GetActorLocation();
			PlaceParticleLine(F_Loc, Enemy_Loc, Fire_Particle, this);
		}
	}
}

