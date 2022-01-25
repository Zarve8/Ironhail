#include "TurrelBasement.h"
#include "UObject/ConstructorHelpers.h"


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
	//DistanceSprite->SetCollisionEnable(ECollisionEnabled::NoCollision);
}
void ATurrelBasement::OnConstruction(const FTransform & Transform) {
	
	//Body->SetVisibility(false, false);
	DistanceSprite->AttachToComponent(Body, FAttachmentTransformRules::SnapToTargetIncludingScale);
	DistanceSprite->SetRelativeRotation(FRotator(0, 0, 90));
	DistanceSprite->SetRelativeLocation(FVector(0, 0, 5));
	DistanceSprite->SetRelativeScale3D(FVector(0.2, 0.2, 0.2));
	
}
void ATurrelBasement::BeginPlay()
{
	PC = Cast<AMain_PC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	Super::BeginPlay();
	SpawnTurrel(Init_Type);
}
void ATurrelBasement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void  ATurrelBasement::CustomOnBeginTouch(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent) {
	PC->SetActiveBasement(this);
	PC->ShowTurrelWidget(TurrelType, level);
	Activate();
}
void  ATurrelBasement::CustomOnEndTouch(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent) {
	UE_LOG(LogTemp, Warning, TEXT("Ended"));
}
void ATurrelBasement::Activate() {

}
void ATurrelBasement::Deactivate() {

}
void  ATurrelBasement::SpawnTurrel(TEnumAsByte<Turel> Type) {
	this->DestroyTurrel();
	TSubclassOf<ATurrel> TType = PC->TFinder->GetTurrelClassByEnum(Type);
	if (!IsValid(TType)) return;
	FVector Loc = this->GetActorLocation();
	ChildTurrel = Cast<ATurrel>(GetWorld()->SpawnActor(TType, &Loc));
}
void  ATurrelBasement::DestroyTurrel() {
	if (IsValid(ChildTurrel)) {
		ChildTurrel->Destroy();
		ChildTurrel = nullptr;
	}
}


