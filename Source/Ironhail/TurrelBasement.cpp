#include "TurrelBasement.h"
#include "UObject/ConstructorHelpers.h"


// ++++++++++ Constrictors ++++++++++
ATurrelBasement::ATurrelBasement()
{
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Base(TEXT("/Game/Source/Turrels/Bases/Base"));
	if (Base.Succeeded())
	{
		Body->SetStaticMesh(Base.Object);
	}
	SetRootComponent(Body);
	Body->OnInputTouchEnter.AddDynamic(this, &ATurrelBasement::CustomOnBeginTouch);
	Body->OnInputTouchLeave.AddDynamic(this, &ATurrelBasement::CustomOnEndTouch);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> DoubleCircle(TEXT("PaperSprite'/Game/Source/HUD/DistanceProjectiles/DoubleCircle_Sprite'"));
	DistanceSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("DistanceProjectile"));
	if (DoubleCircle.Succeeded())
	{
		DistanceSprite->SetSprite(DoubleCircle.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PaperSprite not found"));
	}
	static ConstructorHelpers::FObjectFinder<UPaperSprite> PlaceArrow(TEXT("PaperSprite'/Game/Source/HUD/DistanceProjectiles/ArrowPlacement_Sprite'"));
	PlacementSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PlacementProjectile"));
	if (PlaceArrow.Succeeded())
	{
		PlacementSprite->SetSprite(PlaceArrow.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ArrowSprite not found"));
	}
	//DistanceSprite->SetCollisionEnable(ECollisionEnabled::NoCollision);
}
void ATurrelBasement::OnConstruction(const FTransform & Transform) {
	DistanceSprite->AttachToComponent(Body, FAttachmentTransformRules::SnapToTargetIncludingScale);
	PlacementSprite->AttachToComponent(Body, FAttachmentTransformRules::SnapToTargetIncludingScale);
	DistanceSprite->SetVisibility(false, false);
	PlacementSprite->SetVisibility(false, false);
	DistanceSprite->SetRelativeRotation(FRotator(0, 0, 90));
	DistanceSprite->SetRelativeLocation(FVector(0, 0, 5));
	DistanceSprite->SetRelativeScale3D(FVector(0.2, 0.2, 0.2));
	
}
void ATurrelBasement::BeginPlay()
{
	PC = Cast<AMain_PC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	Super::BeginPlay();
	SpawnTurrel(Init_Type); //Proxy Spawning
}
// ++++++++++ Inputs ++++++++++
void ATurrelBasement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
void  ATurrelBasement::CustomOnBeginTouch(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent) {
	PC->TurrelTouched(this);
}
void  ATurrelBasement::CustomOnEndTouch(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent) {
	UE_LOG(LogTemp, Warning, TEXT("Ended"));
}
// ++++++++++ Turrel Actions ++++++++++
void  ATurrelBasement::SpawnTurrel(TEnumAsByte<Turel> Type) {
	this->DestroyTurrel();
	TSubclassOf<ATurrel> TType = PC->TFinder->GetTurrelClassByEnum(Type);
	if (!IsValid(TType)) return;
	FVector Loc = this->GetActorLocation();
	ChildTurrel = Cast<ATurrel>(GetWorld()->SpawnActor(TType, &Loc));
	TurrelType = Type;
}
void  ATurrelBasement::DestroyTurrel() {
	if (IsValid(ChildTurrel)) {
		ChildTurrel->Destroy();
		ChildTurrel = nullptr;
		SpawnTurrel(E_Empty);
	}
}
// ++++++++++ Show Actions ++++++++++
void ATurrelBasement::Deactivate() {
	DistanceSprite->SetVisibility(false, false);
	PlacementSprite->SetVisibility(false, false);
}
bool ATurrelBasement::ShowForPlacement(){
	if (TurrelType == E_Empty) {
		PlacementSprite->SetVisibility(true, false);
		return true;
	}
	return false;
}
bool ATurrelBasement::ShowActiveTurrel(){
	if (TurrelType != E_Empty) {
		DistanceSprite->SetVisibility(true, false);
		return true;
	}
	return false;
}


