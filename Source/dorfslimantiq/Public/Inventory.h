// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Card.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DORFSLIMANTIQ_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UInventory();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category="Default")
	TArray<UCard*> Cards;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
