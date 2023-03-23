// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hexgrid.generated.h"

UCLASS()
class DORFSLIMANTIQ_API AHexgrid : public AActor {
	GENERATED_BODY()

public:
	AHexgrid();

	UFUNCTION(BlueprintCallable, Category="Default")
	void SetMapSize(float X, float Y);

	UPROPERTY(BlueprintReadWrite, Category="Default")
	float Map_Size_Multiplier;
	
	UPROPERTY(BlueprintReadWrite, Category="Default")
	float Grid_X_Size;

	UPROPERTY(BlueprintReadWrite, Category="Default")
	float Grid_Y_Size;
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
