// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hexgrid.generated.h"

class ATile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FReplaceTile, ATile*, Selected_Tile, const FVector&, Location);


UCLASS()
class DORFSLIMANTIQ_API AHexgrid : public AActor {
	GENERATED_BODY()

public:
	AHexgrid();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Cpp")
	void SetMapSize(float X, float Y);

	UFUNCTION(BlueprintCallable, Category="Cpp")
	void SpawnInitTiles();

	UFUNCTION(BlueprintCallable, Category="Cpp")
	void SpawnGhostTiles(TArray<FVector> Locations);

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite, Category="Default")
	float Map_Size_Multiplier;

	UPROPERTY(BlueprintReadWrite, Category="Default")
	float Grid_X_Size;

	UPROPERTY(BlueprintReadWrite, Category="Default")
	float Grid_Y_Size;

	UPROPERTY(BlueprintReadWrite, Category="Default")
	TObjectPtr<ATile> Target_Tile;

	UPROPERTY(BlueprintReadWrite, Category="Default")
	TArray<TObjectPtr<ATile>> Spawned_Tiles;

	UPROPERTY(BlueprintReadWrite, BlueprintCallable, BlueprintAssignable, Category="Default")
	FReplaceTile OnReplaceTile;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATile> Initial_Tile;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATile> Ghost_Tile;
};
