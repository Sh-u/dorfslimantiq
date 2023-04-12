// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "Card.h"
#include "dorfslimantiq/Public/Utils.h"


AInventory::AInventory() {
}

void AInventory::HandleOnAddCard(UCard* Card) {
	Card->ApplyCardBonus();
	Cards.Push(Card);
	DBG("Card added xdd");
}

void AInventory::BeginPlay() {
	Super::BeginPlay();

	OnAddCard.AddDynamic(this, &AInventory::AInventory::HandleOnAddCard);
}
