#include "PC.h"

#include "CameraPawn.h"
#include "Hexgrid.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


void APC::MoveX(const float Value) {
	const double Speed = FMath::Lerp(Min_Camera_Speed, Max_Camera_Speed, Camera_Zoom);
	Camera_Movement.X = FMath::Clamp(Value, -1.0f, 1.0f) * Speed;
}

void APC::MoveY(const float Value) {
	const double Speed = FMath::Lerp(Min_Camera_Speed, Max_Camera_Speed, Camera_Zoom);
	Camera_Movement.Y = FMath::Clamp(Value, -1.0f, 1.0f) * Speed;
}

void APC::ZoomOut() {
	const float Value = Camera_Zoom - Zoom_Strength;
	const float New_Zoom = FMath::Clamp(Value, 0.1f, 1.0f);
	Camera_Zoom = New_Zoom;
}

void APC::ZoomIn() {
	const float Value = Camera_Zoom + Zoom_Strength;
	const float New_Zoom = FMath::Clamp(Value, 0.1f, 1.0f);
	Camera_Zoom = New_Zoom;
}

void APC::MoveCamera() const {
	if (!Camera_Pawn || !Hexgrid) { return; }

	const FVector Current_Location = Camera_Pawn->GetActorLocation();

	
	FVector New_Location = Camera_Movement + Current_Location;
	New_Location.X = FMath::Clamp(New_Location.X, Hexgrid->Grid_X_Size * -1.0f, Hexgrid->Grid_X_Size);
	New_Location.Y = FMath::Clamp(New_Location.Y, Hexgrid->Grid_Y_Size * -1.0f, Hexgrid->Grid_Y_Size);
	New_Location.Z = 200;
	Camera_Pawn->SetActorLocation(New_Location, false);
	ZoomCamera();
}

void APC::ZoomCamera() const {
	const ACameraPawn* Camera = Cast<ACameraPawn>(Camera_Pawn);
	if (!Camera) return;

	USpringArmComponent* Arm = Camera->FindComponentByClass<USpringArmComponent>();
	if (!Arm) { return; }

	const float Length = FMath::Lerp(Min_Zoom_Distance, Max_Zoom_Distance, Camera_Zoom);
	Arm->TargetArmLength = Length;
}

void APC::BeginPlay() {
	Super::BeginPlay();

	Camera_Pawn = this->GetPawn();
	AActor* Found_Actor = UGameplayStatics::GetActorOfClass(GetWorld(), AHexgrid::StaticClass());
	
	if (!Found_Actor) { return; }
	
	Hexgrid = Cast<AHexgrid>(Found_Actor);
	
	
}

void APC::Tick(const float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	MoveCamera();

	// if(GEngine)
	// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,  *Camera_Movement.ToString());	
}

void APC::SetupInputComponent() {
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveX", this, &APC::MoveX);
	InputComponent->BindAxis("MoveY", this, &APC::MoveY);
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APC::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &APC::ZoomOut);
}
