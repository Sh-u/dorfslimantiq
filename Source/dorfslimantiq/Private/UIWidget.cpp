// Fill out your copyright notice in the Description page of Project Settings.
#include "UIWidget.h"
#include "Tile.h"
#include "TileStack.h"
#include "PC.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"


FText UUIWidget::ShowSelectedItemText() const {
	if (!Tile_Stack || Tile_Stack->Selected_Tile->Tile_Type == ETiletype::Empty) {
		return FText::FromString(TEXT("None"));
	}

	return FText::FromString(GetTileTypeName(Tile_Stack->Selected_Tile->Tile_Type));
}

FText UUIWidget::ShowLevel() const {
	return FText::FromString(FString::FromInt(Player_Controller->Level));
}

FText UUIWidget::ShowScore() const {
	return FText::FromString(FString::FromInt(Player_Controller->Score));
}

FText UUIWidget::ShowThreshold() const {
	return FText::FromString(FString::FromInt(Player_Controller->Threshold));
}

void UUIWidget::AddTextToTileStack() {
	for (const auto Tile : Tile_Stack->Available_Tiles) {
		UTextBlock* Stack_Text = NewObject<UTextBlock>(this);
		Stack_Text->SetText(FText::FromString(GetTileTypeName(Tile)));
		UMG_Tile_Stack_Box->AddChild(Stack_Text);
	}
}


void UUIWidget::NativeConstruct() {
	Super::NativeConstruct();

	Player_Controller = Cast<APC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	Tile_Stack = Cast<ATileStack>(UGameplayStatics::GetActorOfClass(GetWorld(), ATileStack::StaticClass()));
	if (!Player_Controller || !Tile_Stack) {
		UE_LOG(LogTemp, Warning, TEXT("Invalid widget initialization."));
		return;
	}
	AddTextToTileStack();
}

void UUIWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();
	UMG_Selected_Tile_Text->TextDelegate.BindUFunction(this, "ShowSelectedItemText");
	UMG_Score_Text->TextDelegate.BindUFunction(this, "ShowScore");
	UMG_Threshold_Text->TextDelegate.BindUFunction(this, "ShowThreshold");
	UMG_Level_Text->TextDelegate.BindUFunction(this, "ShowLevel");
}
