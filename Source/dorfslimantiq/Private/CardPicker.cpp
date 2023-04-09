// Fill out your copyright notice in the Description page of Project Settings.

#include "CardPicker.h"
#include "Card.h"
#include "MyGameInstance.h"

ACardPicker::ACardPicker() {
	PrimaryActorTick.bCanEverTick = false;
}

void ACardPicker::GenerateCards() {
	if (!Cards.IsEmpty()) {
		Cards.Empty();
	}

	for (int32 i = 0; i < 3; i++) {
		const uint32 N = FMath::RandRange(0, Card_Types.Num() - 1);
		UCard* NewCard = NewObject<UCard>(this, Card_Types[N].GetDefaultObject()->GetClass());
		Cards.Push(NewCard);
	}
}

void ACardPicker::BeginPlay() {
	Super::BeginPlay();

	UMyGameInstance* Game_Instance = Cast<UMyGameInstance>(GetGameInstance());

	if (!Game_Instance) {
		UE_LOG(LogTemp, Warning, TEXT("Game Instance not found -> CardPicker."));
		return;
	}

	Game_Instance->OnLevelUp.AddDynamic(this, &ACardPicker::GenerateCards);
}

void ACardPicker::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
