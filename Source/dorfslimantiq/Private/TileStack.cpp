// Fill out your copyright notice in the Description page of Project Settings.


#include "TileStack.h"
#include "Tile.h"
#include "Tiletype.h"


ATileStack::ATileStack() {
	PrimaryActorTick.bCanEverTick = true;
}

void ATileStack::BeginPlay() {
	Super::BeginPlay();

	AddTilesToStack(10);
	
}

void ATileStack::Tick(const float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ATileStack::AddTilesToStack(const uint32 Amount) {
	for (uint32 i = 0; i < Amount; i++) {
		uint8 n = FMath::RandRange(static_cast<int>(ETiletype::Meadow), static_cast<int>(ETiletype::End) - 1);
		ETiletype Tile_Type = static_cast<ETiletype>(n);
		Available_Tiles.Push(Tile_Type);
	}
}
