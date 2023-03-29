// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tiletype.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"


UCLASS()
class DORFSLIMANTIQ_API ATile : public AActor {
	GENERATED_BODY()

public:
	ATile();
	UFUNCTION(BlueprintCallable, Category="Default")
	TArray<FVector> GenerateAvailableSpawnLocations();
	UFUNCTION(BlueprintCallable, Category="Default")
	void GenerateSocketLocations();
	UFUNCTION(BlueprintImplementableEvent, Category="Default")
	void HandleTileRotate();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	ETiletype Tile_Type;

	UPROPERTY(BlueprintReadWrite, Category="Default")
	TArray<FVector> Socket_Locations;

	

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
