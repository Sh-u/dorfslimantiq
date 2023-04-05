// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "GhostTile.generated.h"

class UScorePopupWidget;
class ATileStack;
class UStaticMeshComponent;
class UScoreRulesBase;
UCLASS()
class DORFSLIMANTIQ_API AGhostTile final : public ATile {
	GENERATED_BODY()

public:
	AGhostTile() : ATile() {
		Score = 0;
	};

	UFUNCTION()
	void Cleanup();

	UFUNCTION()
	void OnMouseOver(UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
	void OnMouseEnd(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void HandleOnRotateSelectedTile();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	int32 Score;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ATileStack> Tile_Stack;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UScorePopupWidget> Score_Popup_Widget;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Initial_SM;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMaterial> Initial_Material;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UScoreRulesBase> Score_Rules;
	UPROPERTY(EditDefaultsOnly, Category="BP_ASSETS")
	TSubclassOf<UScoreRulesBase> Score_Rules_BP;

protected:
	virtual void BeginPlay() override;
};
