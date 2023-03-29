#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC.generated.h"


class APawn;
class AHexgrid;
class ATile;
class ATileStack;
class UUIWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelUp);

UCLASS(Blueprintable, BlueprintType)
class DORFSLIMANTIQ_API APC : public APlayerController {
	GENERATED_BODY()

	// public:
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

	UFUNCTION(BlueprintCallable, Category="Default")
	void HandleOnPickTileFromStack();

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	TObjectPtr<APawn> Camera_Pawn;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	TObjectPtr<AHexgrid> Hexgrid;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	TObjectPtr<ATileStack> Tile_Stack;

	UPROPERTY(BlueprintReadWrite, Category="Default")
	TObjectPtr<UUserWidget> UI;

	UPROPERTY(BlueprintReadWrite, Category="Default")
	TObjectPtr<UUserWidget> Score_Text_Popup;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	int32 Score;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	int32 Threshold;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	int32 Level;

	UPROPERTY
	(BlueprintReadWrite, EditDefaultsOnly, Category="Camera")
	FVector Camera_Movement;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Camera", meta=(ClampMin = "0.1", UIMin = "0.1"))
	float Zoom_Strength;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Camera")
	float Min_Camera_Speed;


	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Camera")
	float Max_Camera_Speed;


	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Camera",
		meta=(ClampMin = "0.1", ClampMax = "1.0", UIMin = "0.1", UIMax = "1.0"))
	float Camera_Zoom;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")
	float Min_Zoom_Distance;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Camera")
	float Max_Zoom_Distance;

	



	// UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	// TArray<TEnumAsByte<E_TileTypes>> inventory;


	// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPickBundle);

	// UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category="Default")
	// FPickBundle PickBundle;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	bool Disable_Tracing;


	UPROPERTY(EditDefaultsOnly, Category="BP_ASSETS")
	TSubclassOf<ATile> BP_Tile;

	UPROPERTY(EditDefaultsOnly, Category = "BP_ASSETS")
	TSubclassOf<UUserWidget> BP_UI;

	UPROPERTY(EditDefaultsOnly, Category = "BP_ASSETS")
	TSubclassOf<UUserWidget> BP_ScorePopup;


	// DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRotateTile);
	//
	// UPROPERTY(BlueprintAssignable, EditDefaultsOnly, Category="Default")
	// FRotateTile RotateTile;
	UPROPERTY(BlueprintReadWrite, BlueprintCallable, BlueprintAssignable, Category="Default")
	FLevelUp OnLevelUp;

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	void MoveX(float Value);
	void MoveY(float Value);
	void ZoomOut();
	void ZoomIn();

	void PlaceTile();
	void RotateSelectedTile();
	void MoveCamera() const;
	void ZoomCamera() const;
};
