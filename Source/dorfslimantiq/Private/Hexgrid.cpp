// Fill out your copyright notice in the Description page of Project Settings.


#include "Hexgrid.h"

AHexgrid::AHexgrid() {
	PrimaryActorTick.bCanEverTick = true;
}

void AHexgrid::SetMapSize(float X, float Y) {
	Grid_X_Size = X *Map_Size_Multiplier;
	Grid_Y_Size = Y * Map_Size_Multiplier;
}

void AHexgrid::BeginPlay() {
	Super::BeginPlay();
	FVector Origin;
	FVector BoxExtent;
	this->GetActorBounds(false,Origin, BoxExtent, true);

	SetMapSize( BoxExtent.X, BoxExtent.Y);
}

void AHexgrid::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
