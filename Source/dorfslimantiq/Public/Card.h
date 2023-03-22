// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Card.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DORFSLIMANTIQ_API UCard : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	UCard();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category="Default")
	virtual void CalculateScore() {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	UTexture2D* Image;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
		
};
