// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "GhostTile.generated.h"

class UMyGameInstance;
class UScorePopupWidget;
class ATileStack;
class UStaticMeshComponent;
class UScoreRulesBase;
class AInventory;

UCLASS()
class DORFSLIMANTIQ_API AGhostTile final : public ATile {
	GENERATED_BODY()

public:
	AGhostTile() : ATile() {
		Calculated_Score = 0;
	};

	UFUNCTION()
	void Cleanup(const bool bIsDestructive);
	UFUNCTION()
	void OnMouseOver(UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
	void OnMouseEnd(UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
	void HandleOnRotateSelectedTile();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	int32 Calculated_Score;


	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMyGameInstance> Game_Instance;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ATileStack> Tile_Stack;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AInventory> Inventory;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UScorePopupWidget> Score_Popup_Widget;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Initial_SM;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMaterial> Initial_Material;

protected:
	virtual void BeginPlay() override;
};
