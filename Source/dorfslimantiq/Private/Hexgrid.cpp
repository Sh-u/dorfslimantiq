// Fill out your copyright notice in the Description page of Project Settings.


#include "Hexgrid.h"
#include "Tile.h"

AHexgrid::AHexgrid() {
	PrimaryActorTick.bCanEverTick = true;
}


void AHexgrid::BeginPlay() {
	Super::BeginPlay();

	SpawnInitialTiles();

	const FVector2D BoxExtent = CalculateGridBounds();
	SetMapSize(BoxExtent.X, BoxExtent.Y);
	// for (const auto Child : this->Children) {
	// 	UE_LOG(LogTemp, Warning, TEXT("Child: %s"), *Child->GetName());
	// }
	
}

void AHexgrid::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}


void AHexgrid::SetMapSize(float X, float Y) {
	Grid_X_Size = X * Map_Size_Multiplier;
	Grid_Y_Size = Y * Map_Size_Multiplier;
}

void AHexgrid::SpawnGhostTiles(TArray<FVector>& Locations) {
	const FAttachmentTransformRules AttachmentRules = ConstructDefaultAttachmentRules();
	UE_LOG(LogTemp, Warning, TEXT("Locations: " ));
	for (auto Location : Locations) {
		UE_LOG(LogTemp, Warning, TEXT("Child: %s"), *Location.ToString());
		ATile* Tile = GetWorld()->SpawnActor<ATile>(Ghost_Tile);
		if (!Tile) continue;
		
		Tile->AttachToActor(this, AttachmentRules);
		Tile->Owner = this;
		Tile->SetActorLocation(Location);
	}
}

FVector2D AHexgrid::CalculateGridBounds() const {
	TArray<AActor*> OutActors;
	GetAttachedActors(OutActors);
	FVector Origin = this->GetActorLocation();
	double X = 0;
	double Y = 0;
	FVector BoxExtent;
	for (const auto Actor : OutActors) {
		Actor->GetActorBounds(false, Origin, BoxExtent, false);
		if (BoxExtent.X > X) {
			X = BoxExtent.X;
		}
		if (BoxExtent.Y > Y) {
			Y = BoxExtent.Y;
		}
	}

	return FVector2D(X, Y);
}

void AHexgrid::HandleReplaceTIle(ATile* Selected_Tile, FVector& Location) {
	const FAttachmentTransformRules Attachment_Rules = ConstructDefaultAttachmentRules();
	Selected_Tile->SetActorLocation(Location);
	Selected_Tile->AttachToActor(this, Attachment_Rules);
	Selected_Tile->GenerateSocketLocations();
	TArray<FVector> Spawn_Locations = Selected_Tile->GenerateAvailableSpawnLocations();
	SpawnGhostTiles(Spawn_Locations);
}


void AHexgrid::SpawnInitialTiles() {
	UE_LOG(LogTemp, Warning, TEXT("Spawn: " ));
	FActorSpawnParameters Spawn_Params;
	Spawn_Params.Owner = this;

	const FRotator Rotator;
	const FVector Spawn_Location = this->GetActorLocation();

	ATile* Tile = GetWorld()->SpawnActor<ATile>(Initial_Tile, Spawn_Location, Rotator, Spawn_Params);
	const FAttachmentTransformRules Attachment_Rules = ConstructDefaultAttachmentRules();
	Tile->AttachToActor(this, Attachment_Rules);
	Tile->Owner = this;
	Tile->GenerateSocketLocations();

	SpawnGhostTiles(Tile->Socket_Locations);
}

FAttachmentTransformRules AHexgrid::ConstructDefaultAttachmentRules() {
	return FAttachmentTransformRules(
		EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
}
