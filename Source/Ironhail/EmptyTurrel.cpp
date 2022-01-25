#include "EmptyTurrel.h"

AEmptyTurrel::AEmptyTurrel() : ATurrel(){

}
void AEmptyTurrel::BeginPlay() {
	Super::BeginPlay();
}
void AEmptyTurrel::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
