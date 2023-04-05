// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScorePopupWidget.generated.h"

class UTextBlock;
class APlayerController;
class APC;

UCLASS()
class DORFSLIMANTIQ_API UScorePopupWidget : public UUserWidget {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	int32 Screen_X_Offset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	int32 Screen_Y_Offset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default" ,meta=(ClampMin= "20", UIMin="20"))
	int32 FontSize_Min;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default",meta=(ClampMin= "30", UIMin="30"))
	int32 FontSize_Max;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Score_Popup_Text;

	UPROPERTY(BlueprintReadOnly, Category="Default")
	FVector Render_Location;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void SetTextLocation();

	UPROPERTY()
	TObjectPtr<APC> Player_Controller;
};
