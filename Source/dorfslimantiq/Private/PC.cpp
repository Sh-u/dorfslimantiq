#include "PC.h"
#include "CameraPawn.h"
#include "CardPicker.h"
#include "GhostTile.h"
#include "Hexgrid.h"
#include "Inventory.h"
#include "MyGameInstance.h"
#include "TileStack.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tile.h"
#include "Tiletype.h"
#include "UIWidget.h"
#include "Components/VerticalBox.h"
#include "Camera/CameraComponent.h"
#include "dorfslimantiq/Public/Utils.h"


void APC::BeginPlay() {
	Super::BeginPlay();

	Game_Instance = Cast<UMyGameInstance>(GetGameInstance());
	Inventory = Cast<AInventory>(
		UGameplayStatics::GetActorOfClass(GetWorld(), BP_Inventory.GetDefaultObject()->GetClass()));
	Tile_Stack = Cast<ATileStack>(UGameplayStatics::GetActorOfClass(GetWorld(), ATileStack::StaticClass()));
	Camera_Pawn = Cast<ACameraPawn>(GetPawn());
	Hexgrid = Cast<AHexgrid>(UGameplayStatics::GetActorOfClass(GetWorld(), AHexgrid::StaticClass()));
	Card_Picker = Cast<ACardPicker>(UGameplayStatics::GetActorOfClass(this, ACardPicker::StaticClass()));
	UI = CreateWidget<UUserWidget>(this, BP_UI);
	UI->AddToViewport();
	Score_Text_Popup = CreateWidget<UUserWidget>(this, BP_ScorePopup);
	Score_Text_Popup->AddToViewport();
	Score_Text_Popup->SetVisibility(ESlateVisibility::Hidden);

	if (!Game_Instance || !Inventory || !Tile_Stack || !Camera_Pawn || !Hexgrid || !Card_Picker || !UI) {
		UE_LOG(LogTemp, Error, TEXT("APC::BeginPlay - Failed to initialize"));
		return;
	}

	Spring_Arm = Camera_Pawn->FindComponentByClass<USpringArmComponent>();
	Camera_Comp = Camera_Pawn->FindComponentByClass<UCameraComponent>();
	if (!Spring_Arm) {
		UE_LOG(LogTemp, Error, TEXT("APC::BeginPlay - Failed to initialize Spring Arm"));
		return;
	}

	Tile_Stack->OnPickTileFromStack.AddDynamic(this, &APC::HandleOnPickTileFromStack);
	Tile_Stack->OnPickTileFromStack.Broadcast();
}

void APC::Tick(const float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	MoveCamera();
}


void APC::PlaceTile() {
	if (!Game_Instance->bEnabledTracing || !Tile_Stack->Selected_Tile) return;

	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (!Hit.bBlockingHit || !IsValid(Hit.GetActor())) return;

	AGhostTile* Tile = Cast<AGhostTile>(Hit.GetActor());

	if (!Tile) return;

	Hexgrid->OnReplaceTile.Broadcast(Tile_Stack->Selected_Tile, Tile->GetActorLocation());

	if (Game_Instance->OnAddScore.IsBound()) {
		Game_Instance->OnAddScore.Execute(Tile->Calculated_Score);
	}

	Tile->Cleanup(true);
	Tile_Stack->OnPickTileFromStack.Broadcast();
}

void APC::HandleOnPickTileFromStack() {
	if (!Tile_Stack->Available_Tiles.IsEmpty()) {
		const ETiletype Tile_Type = Tile_Stack->Available_Tiles[0];
		Tile_Stack->Available_Tiles.RemoveAt(0);
		const UUIWidget* UIWidget = Cast<UUIWidget>(UI);

		if (UIWidget && UIWidget->UMG_Tile_Stack_Box->HasAnyChildren()) {
			UIWidget->UMG_Tile_Stack_Box->RemoveChildAt(0);
		}

		const FVector Location = FVector(0, 800, 200);
		FTransform Transform;
		Transform.SetLocation(Location);
		ATile* Tile = GetWorld()->SpawnActorDeferred<ATile>(BP_Tile, Transform);
		Tile->SetHidden(true);
		Tile->Tile_Type = Tile_Type;
		UGameplayStatics::FinishSpawningActor(Tile, Transform);
		Tile_Stack->Selected_Tile = Tile;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("else"));
		Tile_Stack->Selected_Tile = nullptr;
		//remove from stack widget
	}
}

void APC::RotateSelectedTile() {
	if (!Tile_Stack->Selected_Tile) return;

	FRotator Rotation = Tile_Stack->Selected_Tile->GetActorRotation();
	UE_LOG(LogTemp, Warning, TEXT("ROT :%s"), *Rotation.ToString());
	Rotation.Yaw += 60.0f;
	Tile_Stack->Selected_Tile->SetActorRotation(Rotation);
	Tile_Stack->OnRotateSelectedTile.Broadcast();
}

void APC::MoveCamera() const {
	if (!Camera_Pawn || !Spring_Arm) { return; }

	const FVector Current_Location = Camera_Comp->GetComponentLocation();

	// FVector New_Location = Camera_Movement + Current_Location;
	// New_Location.Y = FMath::Clamp(New_Location.X, Hexgrid->Grid_X_Size * -1.0f, Hexgrid->Grid_X_Size);
	// New_Location.Z = FMath::Clamp(New_Location.Y, Hexgrid->Grid_Y_Size * -1.0f, Hexgrid->Grid_Y_Size);
	// New_Location.X = 200;
	//
	// Camera_Comp->SetWorldLocation(New_Location);
	ZoomCamera();
}

void APC::ZoomCamera() const {
	const float Length = FMath::Lerp(Min_Zoom_Distance, Max_Zoom_Distance, Camera_Zoom);
	Spring_Arm->TargetArmLength = Length;
}


void APC::MoveX(const float Value) {
	if (!Camera_Comp || Value == 0) return;

	const double Speed = FMath::Lerp(Min_Camera_Speed, Max_Camera_Speed, Camera_Zoom) * Value;

	const FVector Current_Location = Camera_Comp->GetComponentLocation();

	FVector Forward_Vector = Camera_Comp->GetForwardVector();

	Forward_Vector.Z = 0;
	Forward_Vector.Normalize();

	FVector New_Location = (Forward_Vector * Speed) + Current_Location;
	const float Max_Clamp_X = Current_Location.X > Hexgrid->Grid_Size.X ? Current_Location.X : Hexgrid->Grid_Size.X;
	const float Max_Clamp_Y = Current_Location.Y > Hexgrid->Grid_Size.Y ? Current_Location.Y : Hexgrid->Grid_Size.Y;
	const float Min_Clamp_X = Current_Location.X < Hexgrid->Grid_Size.X * -1.0f
		                          ? Current_Location.X
		                          : Hexgrid->Grid_Size.X * -1.0f;
	const float Min_Clamp_Y = Current_Location.Y < Hexgrid->Grid_Size.Y * -1.0f
		                          ? Current_Location.Y
		                          : Hexgrid->Grid_Size.Y * -1.0f;

	New_Location.X = FMath::Clamp(New_Location.X, Min_Clamp_X, Max_Clamp_X);
	New_Location.Y = FMath::Clamp(New_Location.Y, Min_Clamp_Y, Max_Clamp_Y);
	Camera_Comp->SetWorldLocation(New_Location);
}

void APC::MoveY(const float Value) {
	if (!Camera_Comp || Value == 0) return;
	const double Speed = FMath::Lerp(Min_Camera_Speed, Max_Camera_Speed, Camera_Zoom) * Value;
	const FVector Current_Location = Camera_Comp->GetComponentLocation();
	FVector Forward_Vector = Camera_Comp->GetRightVector();

	FVector New_Location = (Forward_Vector * Speed) + Current_Location;

	// FVector2D New_Grid = Hexgrid->Grid_Size.GetRotated(Spring_Arm->GetComponentRotation().Yaw);

	const float Max_Clamp_X = Current_Location.X > Hexgrid->Grid_Size.X ? Current_Location.X : Hexgrid->Grid_Size.X;
	const float Max_Clamp_Y = Current_Location.Y > Hexgrid->Grid_Size.Y ? Current_Location.Y : Hexgrid->Grid_Size.Y;
	const float Min_Clamp_X = Current_Location.X < Hexgrid->Grid_Size.X * -1.0f
		                          ? Current_Location.X
		                          : Hexgrid->Grid_Size.X * -1.0f;
	const float Min_Clamp_Y = Current_Location.Y < Hexgrid->Grid_Size.Y * -1.0f
		                          ? Current_Location.Y
		                          : Hexgrid->Grid_Size.Y * -1.0f;

	New_Location.X = FMath::Clamp(New_Location.X, Min_Clamp_X, Max_Clamp_X);
	New_Location.Y = FMath::Clamp(New_Location.Y, Min_Clamp_Y, Max_Clamp_Y);
	Camera_Comp->SetWorldLocation(New_Location);
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

void APC::EnableCameraRotation() {
	bEnabledCameraRotation = true;
}

void APC::DisableCameraRotation() {
	bEnabledCameraRotation = false;
}

void APC::RotateCameraX(float Value) {
	if (!bEnabledCameraRotation) return;

	const float Speed = Value * Camera_Rotation_Speed;
	Spring_Arm->AddWorldRotation(FRotator(0, Speed, 0));
	// Hexgrid->Grid_Size = Hexgrid->Grid_Size.GetRotated(Spring_Arm->GetComponentRotation().Yaw);
}

void APC::RotateCameraY(float Value) {
	if (!bEnabledCameraRotation) return;

	const float Speed = Value * Camera_Rotation_Speed;
	FRotator New_Rotation = Spring_Arm->GetComponentRotation();
	New_Rotation.Pitch = FMath::Clamp(New_Rotation.Pitch + Speed, -50, -30);
	Spring_Arm->SetWorldRotation(New_Rotation);
	FVector Extent = FVector(Hexgrid->Grid_Size.X, Hexgrid->Grid_Size.Y, 0);
	// UKismetSystemLibrary::DrawDebugBox(this, Hexgrid->GetActorLocation(), Extent, FColor::Red, FRotator::ZeroRotator,
	//                                    1.0f, 15);
	// Hexgrid->Grid_Size = Hexgrid->Grid_Size.GetRotated(Spring_Arm->GetComponentRotation().Yaw);
}

void APC::SetupInputComponent() {
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveX", this, &APC::MoveX);
	InputComponent->BindAxis("MoveY", this, &APC::MoveY);
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APC::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &APC::ZoomOut);
	InputComponent->BindAction("PlaceTile", IE_Pressed, this, &APC::PlaceTile);
	InputComponent->BindAction("Rotate", IE_Pressed, this, &APC::RotateSelectedTile);
	InputComponent->BindAction("EnableCameraRotation", IE_Pressed, this, &APC::EnableCameraRotation);
	InputComponent->BindAction("EnableCameraRotation", IE_Released, this, &APC::DisableCameraRotation);
	InputComponent->BindAxis("RotateCameraX", this, &APC::RotateCameraX);
	InputComponent->BindAxis("RotateCameraY", this, &APC::RotateCameraY);
}
