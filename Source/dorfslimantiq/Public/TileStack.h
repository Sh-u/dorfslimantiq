// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tiletype.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileStack.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickTileFromStack);

UCLASS()
class DORFSLIMANTIQ_API ATileStack : public AActor {
	GENERATED_BODY()

public:
	ATileStack();

	UFUNCTION( Category="Default")
	void AddTilesToStack(uint32 Amount);
	
	UPROPERTY(BlueprintReadWrite, Category="Default")
	TArray<ETiletype> Available_Tiles;

	UPROPERTY(BlueprintAssignable, Category="Default")
	FOnPickTileFromStack OnPickTileFromStack;
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
