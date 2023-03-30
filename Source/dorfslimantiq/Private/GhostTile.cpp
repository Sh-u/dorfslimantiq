// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostTile.h"

#include "ScorePopupWidget.h"
#include "TileStack.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetTree.h"
void AGhostTile::BeginPlay() {
	Super::BeginPlay();

	Tile_Stack = Cast<ATileStack>(UGameplayStatics::GetActorOfClass(this, ATileStack::StaticClass()));

	if (!Tile_Stack) return;

	Initial_SM = this->FindComponentByClass<UStaticMeshComponent>();
	Initial_Material = this->Initial_Material->GetMaterial();
	
}

void AGhostTile::NotifyActorBeginCursorOver() {
	Super::NotifyActorBeginCursorOver();

	if (!Tile_Stack->Selected_Tile) return;

	if (!Score_Popup_Widget) {
		Score_Popup_Widget = Cast<UScorePopupWidget>(UWidgetTree::FindWidget(FName(TEXT("WBP_ScorePopup"))));
	}
	
	if (!Score_Popup_Widget) {
		UE_LOG(LogTemp, Warning, TEXT("Not found score popup widget."));
	}
}

void AGhostTile::NotifyActorEndCursorOver() {
	Super::NotifyActorEndCursorOver();
	UE_LOG(LogTemp, Warning, TEXT("End"));
}


