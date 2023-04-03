// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScorePopupWidget.generated.h"

class UTextBlock;
class APlayerController;


UCLASS()
class DORFSLIMANTIQ_API UScorePopupWidget : public UUserWidget {
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetTextLocation();

	
	UPROPERTY()
	TObjectPtr<APlayerController> Player_Controller;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Score_Popup_Text;

	UPROPERTY(BlueprintReadOnly)
	FVector Render_Location;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	
};
