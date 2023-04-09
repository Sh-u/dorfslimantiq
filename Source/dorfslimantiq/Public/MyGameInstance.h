// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

// DECLARE_DELEGATE_OneParam(FAddScore, const int32);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelUp);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddCard, class UCard*, Card);


class ATileStack;

UCLASS()
class DORFSLIMANTIQ_API UMyGameInstance : public UGameInstance {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Default")
	void AddScore(const int32 Score_To_Add);

	UFUNCTION(BlueprintCallable, Category="Default")
	void HandleOnLevelUp();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	TObjectPtr<ATileStack> Tile_Stack;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Score", meta=(ClampMin ="1"))
	int32 Threshold_Multiplier;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Score")
	int32 Score;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Score")
	int32 Threshold;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Score")
	int32 Level;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	bool Disable_Tracing;

	UPROPERTY(BlueprintReadWrite, BlueprintCallable, BlueprintAssignable, Category="Default")
	FLevelUp OnLevelUp;

	UPROPERTY(BlueprintReadWrite, BlueprintCallable, BlueprintAssignable, Category="Default")
	FAddCard OnAddCard;

protected:
	virtual void Init() override;
};
