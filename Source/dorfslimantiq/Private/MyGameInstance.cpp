// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "TileStack.h"
#include "dorfslimantiq/Public/Utils.h"
#include "ScoreRules.h"
#include "Tile.h"
#include "Kismet/GameplayStatics.h"


void UMyGameInstance::Init() {
	Super::Init();
	bEnabledTracing = true;
	Threshold = 100;
	Tile_Stack = Cast<ATileStack>(UGameplayStatics::GetActorOfClass(GetWorld(), ATileStack::StaticClass()));
	if (!Tile_Stack) {
		UE_LOG(LogTemp, Warning, TEXT("Tile stack is not valid -> GameInstance."))
		return;
	}

	OnAddScore.BindUObject(this, &UMyGameInstance::AddScore);
	OnLevelUp.AddDynamic(this, &UMyGameInstance::HandleLevelUp);
	OnEnableTracing.AddDynamic(this, &UMyGameInstance::HandleEnableTracing);
}


int32 UMyGameInstance::CalculateTileScore(const ATile* Base_Tile, const TArray<ATile*> Adjacent_Tiles
) {
	const ETiletype Tiletype = Base_Tile->Tile_Type;
	const FScoreRules* Base_Tile_Rules = Score_Rules.Find(Tiletype);
	if (!Base_Tile_Rules) return 0;

	int32 Calculated_Score = Base_Tile_Rules->Score;
	for (const auto& Tile : Adjacent_Tiles) {
		if (const auto Base_Score = Base_Tile_Rules->Adjacent_Score.Find(Tile->Tile_Type)) {
			Calculated_Score += *Base_Score;
		}
	}

	return Calculated_Score;
}


void UMyGameInstance::AddScore(const int32 Score_To_Add) {
	Score += Score_To_Add;
	if (Score >= Threshold) {
		OnLevelUp.Broadcast();
	}
}

void UMyGameInstance::HandleLevelUp() {
	DBG("LEVEL UP HANDLER");
	Level++;
	Threshold *= Threshold_Multiplier;
	Tile_Stack->AddTilesToStack(5);
}

void UMyGameInstance::HandleEnableTracing(const bool bEnabled) {
	bEnabledTracing = bEnabled;
}
