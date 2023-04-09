// Fill out your copyright notice in the Description page of Project Settings.


#include "CardButton.h"

#include "Card.h"
#include "Components/Button.h"
#include "dorfslimantiq/Public/Utils.h"


void UCardButton::HandleOnClick() {
	DBG("Clicked on me: %s, with card -> %s", *this->GetName(), *Card->GetName());
	
	this->OnClick.Broadcast(Card, this);
}

void UCardButton::NativeConstruct() {
	Super::NativeConstruct();
	
}

void UCardButton::NativeOnInitialized() {
	Super::NativeOnInitialized();
	UMG_Button->OnClicked.AddDynamic(this, &UCardButton::HandleOnClick);
}
