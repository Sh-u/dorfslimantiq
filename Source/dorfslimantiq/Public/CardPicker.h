// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardPicker.generated.h"

class UTextBlock;
class UCard;

UCLASS()
class DORFSLIMANTIQ_API ACardPicker : public AActor {
	GENERATED_BODY()

public:
	ACardPicker();

	UFUNCTION(BlueprintCallable)
	void GenerateCards();

	UPROPERTY(BlueprintReadOnly)
	TArray<UCard*> Cards;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="BP_ASSETS")
	TArray<TSubclassOf<UCard>> Card_Types;
};
