// Fill out your copyright notice in the Description page of Project Settings.


#include "CardButton.h"
#include "Card.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "dorfslimantiq/Public/Utils.h"


void UCardButton::HandleOnClick() {
	DBG("Clicked on me: %s, with card -> %s", *this->GetName(), *Card->GetName());

	this->OnClick.Broadcast(Card, this);
}

void UCardButton::NativeConstruct() {
	Super::NativeConstruct();
}

void UCardButton::UpdateInventoryDisplay() {
	FSlateFontInfo Font = this->UMG_Name->GetFont();
	Font.Size = 20;
	this->UMG_Size_Box->SetMaxDesiredHeight(this->Size_In_Inventory);
	this->UMG_Size_Box->SetMaxDesiredWidth(this->Size_In_Inventory);
	this->UMG_Name->SetFont(Font);
	this->UMG_Description->SetVisibility(ESlateVisibility::Collapsed);
}


void UCardButton::NativeOnInitialized() {
	Super::NativeOnInitialized();
	UMG_Button->OnClicked.AddDynamic(this, &UCardButton::HandleOnClick);
}
