// Fill out your copyright notice in the Description page of Project Settings.


#include "Hexgrid.h"

#include "Tile.h"

AHexgrid::AHexgrid() {
	PrimaryActorTick.bCanEverTick = true;
}

void AHexgrid::SetMapSize(float X, float Y) {
	Grid_X_Size = X * Map_Size_Multiplier;
	Grid_Y_Size = Y * Map_Size_Multiplier;
}

void AHexgrid::SpawnInitTiles() {
	ATile* Child = Initial_Tile.GetDefaultObject();
	if (!Child) return;
	const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(
		EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
	Child->AttachToActor(this, AttachmentRules);
	Child->GenerateSocketLocations();
}

void AHexgrid::SpawnGhostTiles(TArray<FVector> Locations) {
	const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(
		EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
	for (auto Location : Locations) {
		ATile* Child = Ghost_Tile.GetDefaultObject();
		if (!Child) continue;
		Child->AttachToActor(this, AttachmentRules);
		Child->SetActorLocation(Location);
	}
}


void AHexgrid::BeginPlay() {
	Super::BeginPlay();
	FVector Origin;
	FVector BoxExtent;
	this->GetActorBounds(false, Origin, BoxExtent, true);

	SetMapSize(BoxExtent.X, BoxExtent.Y);
}

void AHexgrid::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
