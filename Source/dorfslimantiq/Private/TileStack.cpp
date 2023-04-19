// Fill out your copyright notice in the Description page of Project Settings.


#include "TileStack.h"
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
	TArray<float> Spawn_Values;
	TArray<ETiletype> Spawn_Keys;
	Spawn_Chance.GenerateValueArray(Spawn_Values);
	Spawn_Chance.GenerateKeyArray(Spawn_Keys);

	check(Spawn_Values.Num() == (static_cast<int>(ETiletype::End) - 2));

	float Chance_Sum = 0.f;

	for (const auto Val : Spawn_Values) {
		UE_LOG(LogTemp, Display, TEXT("Val: %f"), Val);
		Chance_Sum += Val;
	}

	for (uint32 i = 0; i < Amount; i++) {
		float Roll = FMath::Floor(FMath::RandRange(0.f, 1.0f) * Chance_Sum);

		UE_LOG(LogTemp, Warning, TEXT("Rolled: %f"), Roll);
		ETiletype Chosen = Spawn_Keys[0];

		for (int32 j = 0; j < Spawn_Values.Num(); j++) {
			Roll -= Spawn_Values[j];
			if (Roll < 0) {
				Chosen = Spawn_Keys[j];
				UE_LOG(LogTemp, Warning, TEXT("Chosen index: %i"), j);
				break;
			}
		}

		Available_Tiles.Push(Chosen);
	}
}
