// Fill out your copyright notice in the Description page of Project Settings.


#include "ScorePopupWidget.h"
#include "Kismet/GameplayStatics.h"

void UScorePopupWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("tick"));
	if (!IsVisible()) return;
	SetTextLocation();
}




void UScorePopupWidget::SetTextLocation() {
	FVector2D Screen_Location;
	Player_Controller->ProjectWorldLocationToScreen(Render_Location, Screen_Location);
	int32 Screen_Width = 0;
	int32 Screen_Height = 0;

	Player_Controller->GetViewportSize(Screen_Width, Screen_Height);
	UE_LOG(LogTemp, Warning, TEXT("Screen_Location: {%s}"), *Screen_Location.ToString());
	this->SetPositionInViewport(Screen_Location);
}


void UScorePopupWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();
	Player_Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!Player_Controller) {
		UE_LOG(LogTemp, Warning, TEXT("Player controller not found (Score popup widget)"));
	}
}

void UScorePopupWidget::NativeConstruct() {
	Super::NativeConstruct();
}
