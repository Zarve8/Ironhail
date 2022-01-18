#include "Turrel.h"

ATurrel::ATurrel()
{
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	if(Body->GetSocketByName(Head_Socket_Name)){
		Head->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform, Head_Socket_Name);
	}
	else {
		Head->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}
	BaseLoc = GetActorLocation();
	PrimaryActorTick.bCanEverTick = true;

}
void ATurrel::BeginPlay()
{
	Super::BeginPlay();
	
}
void ATurrel::Tick(float DeltaTime)
{
	ActionTick(DeltaTime);
	Super::Tick(DeltaTime);

}
Action_AM* ATurrel::GetBaseAction() {
	return new Search_AM(this);
}
//TODO redo if want to roate smoothly
float ATurrel::CalculateRotateTime() {
	if (!IsValid(PreferedEnemy)) return 0.01;
	FVector FaceLoc;
	if (Head->GetSocketByName(Head_Face_Socket_Name)) {
		FaceLoc = Head->GetSocketLocation(Head_Face_Socket_Name);
	}
	else {
		FaceLoc = GetActorLocation();
	}
	FVector N = PreferedEnemy->GetActorLocation() - FaceLoc;
	Target_Rotation = N.Rotation();
	return 0.01;
}
//TODO check for right angle
void ATurrel::StartRotate() {
	float Yaw = Target_Rotation.Yaw;
	float Pitch = Target_Rotation.Pitch;
	Body->SetRelativeRotation(FRotator(0, 0, Yaw));
	Head->SetRelativeRotation(FRotator(Pitch, 0, 0));
}
AWalker* ATurrel::FindAnyEnemy() {
	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWalker::StaticClass(), FoundEnemies);
	int length = FoundEnemies.GetAllocatedSize();
	for (int i = 0; i < length; i++) {
		FVector EnemyLoc = FoundEnemies[i]->GetActorLocation();
		if (fire_distance >= FVector::Distance(BaseLoc, EnemyLoc)) {
			return Cast<AWalker>(FoundEnemies[i]);
		}
	}
	return nullptr;
}
AWalker* ATurrel::FindNearestEnemy() {
	TArray<AActor*> FoundEnemies;
	AActor* NearestEnemy = nullptr;
	float min_distance = fire_distance;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWalker::StaticClass(), FoundEnemies);
	int length = FoundEnemies.GetAllocatedSize();
	for (int i = 0; i < length; i++) {
		FVector EnemyLoc = FoundEnemies[i]->GetActorLocation();
		if (min_distance >= FVector::Distance(BaseLoc, EnemyLoc)) {
			min_distance = FVector::Distance(BaseLoc, EnemyLoc);
			NearestEnemy = FoundEnemies[i];
		}
	}
	return Cast<AWalker>(NearestEnemy);

}
AWalker* ATurrel::FindToughestEnemy() {
	TArray<AActor*> FoundEnemies;
	AWalker* ToughestEnemy = nullptr;
	float max_health = 0;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWalker::StaticClass(), FoundEnemies);
	int length = FoundEnemies.GetAllocatedSize();
	for (int i = 0; i < length; i++) {
		FVector EnemyLoc = FoundEnemies[i]->GetActorLocation();
		AWalker* Walker = Cast<AWalker>(FoundEnemies[i]);
		if (fire_distance >= FVector::Distance(BaseLoc, EnemyLoc) && Walker->health > max_health) {
			max_health = Walker->health;
			ToughestEnemy = Walker;
		}
	}
	return ToughestEnemy;
}
AWalker* ATurrel::FindWeakestEnemy() {
	TArray<AActor*> FoundEnemies;
	AWalker* WeakestEnemy = nullptr;
	float min_health = 100000;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWalker::StaticClass(), FoundEnemies);
	int length = FoundEnemies.GetAllocatedSize();
	for (int i = 0; i < length; i++) {
		FVector EnemyLoc = FoundEnemies[i]->GetActorLocation();
		AWalker* Walker = Cast<AWalker>(FoundEnemies[i]);
		float w_health = Walker->health / Walker->armour_cof;
		if (fire_distance >= FVector::Distance(BaseLoc, EnemyLoc) && w_health < min_health) {
			min_health = w_health;
			WeakestEnemy = Walker;
		}
	}
	return WeakestEnemy;
}
