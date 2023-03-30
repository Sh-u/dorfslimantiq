// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIWidget.generated.h"

class UVerticalBox;
class ATileStack;
class UTextBlock;
class APC;
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
	
	UPROPERTY(BlueprintReadOnly, Category="Default")
	TObjectPtr<APC> Player_Controller;

	UPROPERTY(BlueprintReadWrite, Category="Default")
	TObjectPtr<ATileStack> Tile_Stack;

	UPROPERTY(BlueprintReadOnly, Category="Default")
	TObjectPtr<UVerticalBox> UMG_Tile_Stack_Box;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
private:

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> UMG_Selected_Tile_Text;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> UMG_Score_Text;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> UMG_Threshold_Text;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> UMG_Level_Text;

	UPROPERTY(EditDefaultsOnly, Category="BP_ASSETS")
	TSubclassOf<ATileStack> BP_Tile_Stack;
};
