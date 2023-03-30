// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "GhostTile.generated.h"

class UScorePopupWidget;
class ATileStack;
class UStaticMeshComponent;
UCLASS()
class DORFSLIMANTIQ_API AGhostTile final : public ATile {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ATileStack> Tile_Stack;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UScorePopupWidget> Score_Popup_Widget;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Initial_SM;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMaterial> Initial_Material;

protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginCursorOver() override;
	virtual void NotifyActorEndCursorOver() override;
};
