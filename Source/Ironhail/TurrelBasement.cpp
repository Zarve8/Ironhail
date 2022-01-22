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
	//Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//Body->SetCollisionEnabled(true);
	//Body->OnBeginCursorOver.AddDynamic(this, &ATurrelBasement::CustomOnBeginMouseOver);
	Body->OnInputTouchEnter.AddDynamic(this, &ATurrelBasement::CustomOnBeginTouch);
	Body->OnInputTouchLeave.AddDynamic(this, &ATurrelBasement::CustomOnEndTouch);
	static ConstructorHelpers::FObjectFinder<UPaperSprite> DoubleCircle(TEXT("PaperSprite'/Game/Content/Source/HUD/DistanceProjectiles/DoubleCircle_Sprite'"));
	DistanceSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("DistanceProjectile"));
	if (DoubleCircle.Succeeded())
	{
		DistanceSprite->SetSprite(DoubleCircle.Object);
	}
}
void ATurrelBasement::OnConstruction(const FTransform & Transform) {
	SetRootComponent(Body);
	Body->SetVisibility(false, false);
	DistanceSprite->AttachToComponent(Body, FAttachmentTransformRules::SnapToTargetIncludingScale);
	DistanceSprite->SetRelativeRotation(FRotator(90, 0, 0));
	
}
void ATurrelBasement::BeginPlay()
{
	Super::BeginPlay();
	
}
void ATurrelBasement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void  ATurrelBasement::CustomOnBeginTouch(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent) {
	UE_LOG(LogTemp, Warning, TEXT("Triggered"));
}
void  ATurrelBasement::CustomOnEndTouch(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent) {
	UE_LOG(LogTemp, Warning, TEXT("Ended"));
}


