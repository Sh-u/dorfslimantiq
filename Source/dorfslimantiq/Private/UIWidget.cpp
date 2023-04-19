// Fill out your copyright notice in the Description page of Project Settings.
#include "UIWidget.h"
#include "Card.h"
#include "CardButton.h"
#include "CardPicker.h"
#include "Inventory.h"
#include "MyGameInstance.h"
#include "Tile.h"
#include "TileStack.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/ScaleBox.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Overlay.h"
#include "Blueprint/WidgetTree.h"
#include "dorfslimantiq/Public/Utils.h"
#include "Kismet/GameplayStatics.h"


FText UUIWidget::ShowSelectedItemText() const {
	if (!Tile_Stack->Selected_Tile || Tile_Stack->Selected_Tile->Tile_Type == ETiletype::Empty) {
		return FText::FromString(TEXT("None"));
	}

	return FText::FromString(GetTileTypeName(Tile_Stack->Selected_Tile->Tile_Type));
}

FText UUIWidget::ShowLevel() const {
	return FText::FromString(FString::FromInt(Game_Instance->Level));
}

FText UUIWidget::ShowScore() const {
	return FText::FromString(FString::FromInt(Game_Instance->Score));
}

FText UUIWidget::ShowThreshold() const {
	return FText::FromString(FString::FromInt(Game_Instance->Threshold));
}

void UUIWidget::AddTextToTileStack() {
	UMG_Tile_Stack_Box->ClearChildren();
	for (const auto Tile : Tile_Stack->Available_Tiles) {
		UTextBlock* Stack_Text = NewObject<UTextBlock>(this);
		Stack_Text->SetText(FText::FromString(GetTileTypeName(Tile)));
		UMG_Tile_Stack_Box->AddChild(Stack_Text);
	}
}


void UUIWidget::HandleOnCardChosen(UCard* Chosen_Card, UCardButton* UMG_Card) {
	UMG_Card->OnClick.RemoveDynamic(this, &UUIWidget::HandleOnCardChosen);
	UMG_Card_Picker_Container->SetVisibility(ESlateVisibility::Hidden);
	UMG_Card_Picker_Box->ClearChildren();
	UMG_Card->UpdateInventoryDisplay();
	UMG_Inventory_Box->AddChild(UMG_Card);
	Inventory->OnAddCard.Broadcast(Chosen_Card);
	Game_Instance->OnEnableTracing.Broadcast(true);
	UMG_Card->OnClick.AddDynamic(this, &UUIWidget::HandleShowCardDetails);
}

void UUIWidget::HandleShowCardDetails(UCard* Chosen_Card, UCardButton* UMG_Card) {
	
	UMG_Card_Details_Container->SetVisibility(ESlateVisibility::Visible);
	Game_Instance->OnEnableTracing.Broadcast(false);
	
	if (Last_Card_Showed == UMG_Card) {
		DBG("Same :D");
		return;
	}
	DBG("Not same :D");
	UMG_Card_Details_Image->SetBrushFromTexture(Chosen_Card->Image);
	UMG_Card_Details_Exit_Btn->OnClicked.AddDynamic(this, &UUIWidget::HideCardDetails);
	UMG_Card_Details_Name->SetText(FText::FromString(Chosen_Card->Name));
	UMG_Card_Details_Description->SetText(FText::FromString(Chosen_Card->Description));
	Last_Card_Showed = UMG_Card;
}

void UUIWidget::HandleLevelUp() {
	DBG("Cards to choose: %i", Card_Picker->Cards.Num());
	if (Card_Picker->Cards.Num() != 3) return;

	UMG_Card_Picker_Container->SetVisibility(ESlateVisibility::Visible);
	Game_Instance->OnEnableTracing.Broadcast(false);

	for (const auto& Card : Card_Picker->Cards) {
		UCardButton* UMG_Card_Button = CreateWidget<UCardButton>(this, BP_CardButton);

		if (!UMG_Card_Button) continue;

		UMG_Card_Button->OnClick.AddDynamic(this, &UUIWidget::HandleOnCardChosen);
		UMG_Card_Button->Card = Card;
		UMG_Card_Picker_Box->AddChild(UMG_Card_Button);

		if (!UMG_Card_Button->UMG_Button) continue;

		FButtonStyle Style = UMG_Card_Button->UMG_Button->WidgetStyle;
		Style.Normal.SetResourceObject(Card->Image);
		Style.Hovered.SetResourceObject(Card->Image);
		Style.Pressed.SetResourceObject(Card->Image);
		UMG_Card_Button->UMG_Button->SetStyle(Style);
		UMG_Card_Button->UMG_Name->SetText(FText::FromString(Card->Name));
		UMG_Card_Button->UMG_Description->SetText(FText::FromString(Card->Description));
	}

	AddTextToTileStack();
}

void UUIWidget::HideCardDetails() {
	UMG_Card_Details_Container->SetVisibility(ESlateVisibility::Collapsed);
	Game_Instance->OnEnableTracing.Broadcast(true);
}

void UUIWidget::NativeConstruct() {
	Super::NativeConstruct();

	AddTextToTileStack();
}

void UUIWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

	Game_Instance = Cast<UMyGameInstance>(GetGameInstance());
	Tile_Stack = Cast<ATileStack>(UGameplayStatics::GetActorOfClass(GetWorld(), ATileStack::StaticClass()));
	Card_Picker = Cast<ACardPicker>(UGameplayStatics::GetActorOfClass(GetWorld(), ACardPicker::StaticClass()));
	Inventory = Cast<AInventory>(UGameplayStatics::GetActorOfClass(GetWorld(), AInventory::StaticClass()));
	if (!Game_Instance || !Tile_Stack || !Card_Picker || !Inventory) {
		UE_LOG(LogTemp, Warning,
		       TEXT("Game Instance or Tile Stack or Card Picker or Inventory not found -> UIWidget."));
		return;
	}
	Game_Instance->OnLevelUp.AddDynamic(this, &UUIWidget::HandleLevelUp);

	UMG_Selected_Tile_Text->TextDelegate.BindUFunction(this, "ShowSelectedItemText");
	UMG_Score_Text->TextDelegate.BindUFunction(this, "ShowScore");
	UMG_Threshold_Text->TextDelegate.BindUFunction(this, "ShowThreshold");
	UMG_Level_Text->TextDelegate.BindUFunction(this, "ShowLevel");
}
