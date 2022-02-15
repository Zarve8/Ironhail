#include "Turrel.h"


// ++++++++++ Constructors ++++++++++
ATurrel::ATurrel()
{
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	SetRootComponent(Body);
	Head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	Head->SetupAttachment(RootComponent);
	PrimaryActorTick.bCanEverTick = true;
	this->SetActorEnableCollision(ECollisionEnabled::NoCollision);
}
void ATurrel::OnConstruction(const FTransform & Transform) {
	BaseLoc= Transform.GetLocation();
	if (Body->GetSocketByName(Head_Socket_Name)) {
		Head->AttachToComponent(Body, FAttachmentTransformRules::SnapToTargetIncludingScale, Head_Socket_Name);
	}
	else {
		Head->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		UE_LOG(LogTemp, Error, TEXT("Head Socket not found"));
	}
	Head->SetRelativeScale3D(Head_Scale);
}
void ATurrel::BeginPlay()
{
	this->SetActorEnableCollision(ECollisionEnabled::NoCollision);
	BackUp_Stats();
	ActionBeginPlay();
	Super::BeginPlay();
}
void ATurrel::Tick(float DeltaTime)
{
	ActionTick(DeltaTime);
	Super::Tick(DeltaTime);

}
// ++++++++++ Functions for ActionMachine ++++++++++
Action_AM* ATurrel::GetBaseAction() {
	//UE_LOG(LogTemp, Error, TEXT("GetBaseAction"));
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
		UE_LOG(LogTemp, Error, TEXT("No Face Socket"));   
	}
	FVector N = FaceLoc - PreferedEnemy->GetActorLocation();
	Target_Rotation = N.Rotation();
	return 0.01;
}
void ATurrel::StartRotate() {
	float Yaw = Target_Rotation.Yaw;
	float Pitch = Target_Rotation.Pitch;
	float Roll = Target_Rotation.Roll;
	this->SetActorRotation(FRotator(0, Yaw, 0));
	Head->SetRelativeRotation(FRotator(Pitch, 0, 0));
}
// ++++++++++ Finding Enemy ++++++++++
AWalker* ATurrel::FindAnyEnemy() {
	TArray<AActor*> FoundEnemies;
	BaseLoc = GetActorLocation();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWalker::StaticClass(), FoundEnemies);
	int i = 0;
	while(FoundEnemies.IsValidIndex(i)){
		FVector EnemyLoc = FoundEnemies[i]->GetActorLocation();
		if (fire_distance >= FVector::Distance(BaseLoc, EnemyLoc)) {
			return Cast<AWalker>(FoundEnemies[i]);
		}
		i++;
	}
	return nullptr;
}
//
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
//
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
// ++++++++++ Modifiers Funcs ++++++++++
void ATurrel::BackUp_Stats() {
	base_reload_time = reload_time;
	base_shoot_time = shoot_time;
	base_fire_distance = fire_distance;
	base_damage = damage;
	base_is_freeze = is_freeze;
	base_freeze_time = freeze_time;
	base_is_lightning = is_lightning;
	base_lightning_count = lightning_count;
	base_lightning_damage = lightning_damage;
	base_is_burn = is_burn;
	base_burning_time = burning_time;
	base_burning_damage = burning_damage;
}
void ATurrel::Reset_Mod() {
	reload_time = base_reload_time;
	shoot_time = base_shoot_time;
	fire_distance = base_fire_distance;
	damage = base_damage;
	is_freeze = base_is_freeze;
	freeze_time = base_freeze_time;
	is_lightning = base_is_lightning;
	lightning_count = base_lightning_count;
	lightning_damage = base_lightning_damage;
	is_burn = base_is_burn;
	burning_time = base_burning_time;
	burning_damage = base_burning_damage;
	bullet_speed_cof = 1.0;
}
void ATurrel::Apply_Mod(TEnumAsByte<Mod> NMod) {
	switch (NMod) {
			case E_RapidFire:
				reload_time *= 0.8;
				return;
			case E_HighDamage:
				damage *= 1.2;
				return;
			case E_Pesto:
				bullet_speed_cof *= 1.25;
				return;
			case E_Frost:
				is_freeze = true;
				freeze_time += additive_freeze_time;
				return;
			case E_Burn:
				is_burn = true;
				burning_time += additive_burn_time;
				return;
			case E_LongRange:
				fire_distance += 2000;
				return;
			case E_Lightning:
				is_lightning = true;
				lightning_count += 1;
			default:
				return;
	}
}
void ATurrel::Apply_Array_Mod(TArray<TEnumAsByte<Mod>> NArray) {
	Reset_Mod();
	int index = 0;
	while (NArray.IsValidIndex(index)) {
		Apply_Mod(NArray[index]);
		index++;
	}
}
