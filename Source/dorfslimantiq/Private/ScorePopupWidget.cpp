// Fill out your copyright notice in the Description page of Project Settings.


#include "ScorePopupWidget.h"
#include "PC.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UScorePopupWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!IsVisible()) return;
	SetTextLocation();
}

void UScorePopupWidget::SetTextLocation() {
	FVector2D Screen_Location;
	Player_Controller->ProjectWorldLocationToScreen(Render_Location, Screen_Location);
	int32 Screen_Width = 0;
	int32 Screen_Height = 0;

	Screen_Location.X += Screen_X_Offset;
	Screen_Location.Y += Screen_Y_Offset;

	FSlateFontInfo Current_Font = Score_Popup_Text->GetFont();
	Current_Font.Size = FMath::Lerp(FontSize_Min, FontSize_Max, Player_Controller->Camera_Zoom);
	Score_Popup_Text->SetFont(Current_Font);

	Player_Controller->GetViewportSize(Screen_Width, Screen_Height);
	this->SetPositionInViewport(Screen_Location);
}


void UScorePopupWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();
	Player_Controller = Cast<APC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!Player_Controller) {
		UE_LOG(LogTemp, Warning, TEXT("Player controller not found (Score popup widget)"));
	}
}

void UScorePopupWidget::NativeConstruct() {
	Super::NativeConstruct();
}
