// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScoreRules.h"
#include "Blueprint/UserWidget.h"
#include "UIWidget.generated.h"

class UImage;
class ACardPicker;
class UMyGameInstance;
class UVerticalBox;
class ATileStack;
class UTextBlock;
class UScaleBox;
class UOverlay;
class UButton;
class UHorizontalBox;
class UCardButton;
class AInventory;
UCLASS()
class DORFSLIMANTIQ_API UUIWidget : public UUserWidget {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FText ShowSelectedItemText() const;

	UFUNCTION(BlueprintCallable)
	FText ShowLevel() const;

	UFUNCTION(BlueprintCallable)
	FText ShowScore() const;

	UFUNCTION(BlueprintCallable)
	FText ShowThreshold() const;

	UFUNCTION(BlueprintCallable)
	void AddTextToTileStack();

	UFUNCTION(BlueprintCallable)
	void HandleOnCardChosen(class UCard* Chosen_Card, class UCardButton* UMG_Card);

	UFUNCTION(BlueprintCallable)
	void HandleShowCardDetails(class UCard* Chosen_Card, class UCardButton* UMG_Card);

	UFUNCTION(BlueprintCallable)
	void HandleLevelUp();


	UFUNCTION()
	void HideCardDetails();

	UPROPERTY(BlueprintReadOnly, Category="Default")
	TObjectPtr<UMyGameInstance> Game_Instance;

	UPROPERTY(BlueprintReadWrite, Category="Default")
	TObjectPtr<ATileStack> Tile_Stack;

	UPROPERTY(BlueprintReadWrite, Category="Default")
	TObjectPtr<ACardPicker> Card_Picker;

	UPROPERTY(EditDefaultsOnly, Category="Default")
	TObjectPtr<AInventory> Inventory;

	UPROPERTY(BlueprintReadOnly, Category="Default")
	TObjectPtr<UVerticalBox> UMG_Tile_Stack_Box;

	UPROPERTY(BlueprintReadOnly, Category="Default")
	TObjectPtr<UHorizontalBox> UMG_Inventory_Box;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UHorizontalBox> UMG_Card_Picker_Box;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UScaleBox> UMG_Card_Picker_Container;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> UMG_Selected_Tile_Text;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> UMG_Score_Text;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> UMG_Threshold_Text;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> UMG_Level_Text;

	// Card Details Tab
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UOverlay> UMG_Card_Details_Container;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> UMG_Card_Details_Image;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> UMG_Card_Details_Exit_Btn;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> UMG_Card_Details_Name;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> UMG_Card_Details_Description;

	UCardButton* Last_Card_Showed;
	
	UPROPERTY(EditDefaultsOnly, Category="BP_ASSETS")
	TSubclassOf<ATileStack> BP_Tile_Stack;

	UPROPERTY(EditDefaultsOnly, Category="BP_ASSETS")
	TSubclassOf<UCardButton> BP_CardButton;
};
