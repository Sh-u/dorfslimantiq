#include "PC.h"

#include "CameraPawn.h"
#include "Hexgrid.h"

#include "TileStack.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tile.h"
#include "Tiletype.h"


void APC::BeginPlay() {
	Super::BeginPlay();

	AActor* TileStack_Actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATileStack::StaticClass());
	Tile_Stack = Cast<ATileStack>(TileStack_Actor);
	if (!Tile_Stack) {
		UE_LOG(LogTemp, Warning, TEXT("Null tile stack"));
		return;
	}
	Tile_Stack->OnPickTileFromStack.AddDynamic(this, &APC::HandleOnPickTileFromStack);
	Tile_Stack->OnPickTileFromStack.Broadcast();
	APawn* Found_Pawn = this->GetPawn();
	Camera_Pawn = Cast<ACameraPawn>(Found_Pawn);
	if (!Camera_Pawn) return;
	AActor* Hexgrid_Actor = UGameplayStatics::GetActorOfClass(GetWorld(), AHexgrid::StaticClass());

	if (!Hexgrid_Actor) { return; }

	Hexgrid = Cast<AHexgrid>(Hexgrid_Actor);
}

void APC::Tick(const float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	MoveCamera();

	// if(GEngine)
	// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,  *Camera_Movement.ToString());	
}


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

void APC::PlaceTile() {
	UE_LOG(LogTemp, Warning, TEXT("PLACE TILE 1"));
	if (Disable_Raycast || !Selected_Tile_Actor) return;
	FHitResult Hit;
	UE_LOG(LogTemp, Warning, TEXT("PLACE TILE 2"));
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	UE_LOG(LogTemp, Warning, TEXT("PLACE TILE 3: %s"), *Hit.GetActor()->GetName());

	if (!Hit.bBlockingHit || !IsValid(Hit.GetActor())) return;
	ATile* Tile = Cast<ATile>(Hit.GetActor());
	UE_LOG(LogTemp, Warning, TEXT("PLACE TILE 3: %s"), *GetTileTypeName(Tile->Tile_Type));
	if (Tile->Tile_Type != ETiletype::Ghost) return;
	
	Hexgrid->OnReplaceTile.Broadcast(Selected_Tile_Actor, Tile->GetActorLocation());
	Tile->Destroy();
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
	if (!Camera_Pawn) return;

	USpringArmComponent* Arm = Camera_Pawn->FindComponentByClass<USpringArmComponent>();
	if (!Arm) { return; }

	const float Length = FMath::Lerp(Min_Zoom_Distance, Max_Zoom_Distance, Camera_Zoom);
	Arm->TargetArmLength = Length;
}


void APC::HandleOnPickTileFromStack() {
	UE_LOG(LogTemp, Warning, TEXT("CALLING PICK ITEM"));
	if (!Tile_Stack->Available_Tiles.IsEmpty()) {
		const ETiletype Tile_Type = Tile_Stack->Available_Tiles[0];
		Tile_Stack->Available_Tiles.RemoveAt(0);
		Selected_Tile_Type = Tile_Type;
		//remove from ui widget
		const FVector Location = FVector(0, 800, 0);
		FTransform Transform;
		Transform.SetLocation(Location);

		ATile* Tile = GetWorld()->SpawnActorDeferred<ATile>(BP_Tile, Transform);
		Tile->Tile_Type = Tile_Type;
		UGameplayStatics::FinishSpawningActor(Tile, Transform);
		Selected_Tile_Actor = Tile;
	}
	else {
		Selected_Tile_Actor = nullptr;
		//remove from stack widget
	}
}

void APC::SetupInputComponent() {
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveX", this, &APC::MoveX);
	InputComponent->BindAxis("MoveY", this, &APC::MoveY);
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APC::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &APC::ZoomOut);
	InputComponent->BindAction("PlaceTile", IE_Pressed, this, &APC::PlaceTile);
}
