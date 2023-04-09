// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "TileStack.h"
#include "dorfslimantiq/Public/Utils.h"
#include "Kismet/GameplayStatics.h"


void UMyGameInstance::AddScore(const int32 Score_To_Add) {
	Score += Score_To_Add;
	if (Score >= Threshold) {
		OnLevelUp.Broadcast();
	}
}

void UMyGameInstance::HandleOnLevelUp() {
	DBG("LEVEL UP HANDLER");
	Level++;
	Threshold *= Threshold_Multiplier;
	Tile_Stack->AddTilesToStack(5);
}

void UMyGameInstance::Init() {
	Super::Init();

	Threshold = 100;
	Tile_Stack = Cast<ATileStack>(UGameplayStatics::GetActorOfClass(GetWorld(), ATileStack::StaticClass()));
	if (!Tile_Stack) {
		UE_LOG(LogTemp, Warning, TEXT("Tile stack is not valid -> GameInstance."))
		return;
	}

	// OnAddScore.BindUObject(this, &UMyGameInstance::AddScore);
	OnLevelUp.AddDynamic(this, &UMyGameInstance::HandleOnLevelUp);
}
