#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC.generated.h"


class APawn;
class AHexgrid;
class ATile;
UCLASS(Blueprintable, BlueprintType)
class DORFSLIMANTIQ_API APC : public APlayerController {
	GENERATED_BODY()

	// public:
	// 	UFUNCTION(BlueprintCallable)
	// 	void moveCamera();
	//
	//
	// 	UFUNCTION(BlueprintCallable)
	// 	void setMapSize(double box_extent_x, double box_extent_y);
	//
	//
	// 	UFUNCTION(BlueprintCallable)
	// 	void addCardToInventory();
	//
	//
	// 	UFUNCTION(BlueprintCallable)
	// 	void getAvailableBundles();
	//
	//
	// 	UFUNCTION(BlueprintCallable)
	// 	void addScore(int32 score_to_add);
	//
	//
	// 	UFUNCTION(BlueprintCallable)
	// 	void spawnBundles();

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	TObjectPtr<APawn> Camera_Pawn;
	//
	//
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	TObjectPtr<AHexgrid> Hexgrid;


	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Tile")
	TObjectPtr<ATile> Selected_Tile_Actor;
	
	//
	//
	// UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	// double grid_x_size;
	//
	//
	// UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	// double grid_y_size;


	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Camera")
	FVector Camera_Movement;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Camera", meta=(ClampMin = "0.1", UIMin = "0.1"))
	float Zoom_Strength;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Camera")
	float Min_Camera_Speed;


	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Camera")
	float Max_Camera_Speed;


	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Camera", meta=(ClampMin = "0.1", ClampMax = "1.0", UIMin = "0.1", UIMax = "1.0"))
	float Camera_Zoom;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")
	float Min_Zoom_Distance;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")
	float Max_Zoom_Distance;


	// UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	// double mouse_x;
	//
	//
	// UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	// double mouse_y;


	// DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReplaceTile, FVector, spawn_location, ABP_Tile_C*, target_tile,
	//                                                int32, score_to_add);

	// UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category="Default")
	// FReplaceTile ReplaceTile;


	// UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	// int32 score;
	//
	//
	// UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	// int32 threshold;
	//
	//
	// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelUp);
	//
	// UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category="Default")
	// FLevelUp LevelUp;
	//
	//
	// UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	// int32 level;


	// UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	// TArray<TEnumAsByte<E_TileTypes>> inventory;


	// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPickBundle);

	// UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category="Default")
	// FPickBundle PickBundle;


	// UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	// bool disable_raycasting;


	// UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	// TEnumAsByte<E_TileTypes> selected_tile;


	// UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	// TObjectPtr<UWBP_UI_C> UI;


	// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPickItemFromStack);
	//
	// UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category="Default")
	// FPickItemFromStack PickItemFromStack;


	// UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	// TObjectPtr<ABP_TileStack_C> tile_stack;


	


	// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRotateTile);
	//
	// UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category="Default")
	// FRotateTile RotateTile;


	// UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	// TObjectPtr<UWBP_ScorePopup_C> score_text_popup;


	// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCreatedScorePopupWidget);
	//
	// UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category="Default")
	// FCreatedScorePopupWidget CreatedScorePopupWidget;

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	void MoveX(float Value);
	void MoveY(float Value);
	void ZoomOut();
	void ZoomIn();

	void MoveCamera() const;
	void ZoomCamera() const;
};
