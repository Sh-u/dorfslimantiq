// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hexgrid.generated.h"

class ATile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FReplaceTile, ATile*, Selected_Tile, const FVector&, Location);


UCLASS(Blueprintable)
class DORFSLIMANTIQ_API AHexgrid : public AActor {
	GENERATED_BODY()

public:
	AHexgrid();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Default")
	void SetMapSize(const float X, const float Y);

	UFUNCTION(BlueprintCallable, Category="Default")
	void SpawnGhostTiles(UPARAM(ref) TArray<FVector>& Locations);

	UFUNCTION(BlueprintCallable)
	FVector2D CalculateGridBounds() const;

	UFUNCTION(BlueprintCallable)
	void HandleReplaceTIle(ATile* Selected_Tile, UPARAM(ref) FVector& Location);
	
	UFUNCTION(BlueprintCallable)
	void SpawnInitialTiles();


	static FAttachmentTransformRules ConstructDefaultAttachmentRules();
	
	UPROPERTY()
	bool Spawned;
protected:
	virtual void BeginPlay() override;
	

public:

	UPROPERTY(BlueprintReadWrite, Category="Default")
	TObjectPtr<ATile> Target_Tile;

	UPROPERTY(BlueprintReadWrite, Category="Default")
	TArray<TObjectPtr<ATile>> Spawned_Tiles;

	
	UPROPERTY(BlueprintReadWrite, Category="Default")
	float Map_Size_Multiplier;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	float Grid_X_Size;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	float Grid_Y_Size;
	

	UPROPERTY(EditDefaultsOnly, Category="BP_ASSETS")
	TSubclassOf<ATile> Initial_Tile;

	UPROPERTY(EditDefaultsOnly, Category="BP_ASSETS")
	TSubclassOf<ATile> Ghost_Tile;


	UPROPERTY(BlueprintReadWrite, BlueprintCallable, BlueprintAssignable, Category="Game|Cpp")
	FReplaceTile OnReplaceTile;
	
};
