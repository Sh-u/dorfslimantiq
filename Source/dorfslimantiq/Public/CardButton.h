// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CardButton.generated.h"

class UButton;
class UCard;
class UImage;
class UTextBlock;
class USizeBox;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FClick, UCard*, Card, UCardButton*, UMG_Card);


UCLASS()
class DORFSLIMANTIQ_API UCardButton : public UUserWidget {
	GENERATED_BODY()

public:
	UFUNCTION()
	void HandleOnClick();

	UFUNCTION()
	void UpdateInventoryDisplay();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	int32 Size_In_Inventory;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<UCard> Card;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> UMG_Button;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> UMG_Name;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> UMG_Description;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USizeBox> UMG_Size_Box;

	UPROPERTY()
	FClick OnClick;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
};
