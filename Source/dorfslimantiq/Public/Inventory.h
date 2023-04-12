// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inventory.generated.h"
class UCard;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddCard, UCard*, Card);

UCLASS(Blueprintable)
class DORFSLIMANTIQ_API AInventory : public AActor {
	GENERATED_BODY()

public:
	AInventory();
	UFUNCTION(BlueprintCallable)
	void HandleOnAddCard(UCard* Card);

	UPROPERTY(BlueprintReadWrite, BlueprintCallable, BlueprintAssignable, Category="Events")
	FAddCard OnAddCard;

	TArray<UCard*> GetCards() { return Cards; };

protected:
	virtual void BeginPlay() override;

private:
	TArray<UCard*> Cards;
};
