#include "Card.h"


UCard::UCard() {
	PrimaryComponentTick.bCanEverTick = true;

	this->Name = "Card Name";
	this->Description = "Description";
}

void UCard::BeginPlay() {
	Super::BeginPlay();
}

void UCard::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
