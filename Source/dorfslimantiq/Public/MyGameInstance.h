// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ScoreRules.h"
#include "MyGameInstance.generated.h"

DECLARE_DELEGATE_OneParam(FAddScore, const int32);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelUp);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnableTracing, const bool, bEnabled);

class ATileStack;
class ATile;


UCLASS()
class DORFSLIMANTIQ_API UMyGameInstance : public UGameInstance {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Default")
	int32 CalculateTileScore(const ATile* Base_Tile, const TArray<ATile*> Adjacent_Tiles);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	TMap<ETiletype, FScoreRules> Score_Rules;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default", meta=(ClampMin ="1"))
	int32 Threshold_Multiplier;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	int32 Score;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	int32 Threshold;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	int32 Level;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	bool bEnabledTracing;

	UPROPERTY(BlueprintReadWrite, BlueprintCallable, BlueprintAssignable, Category="Events")
	FLevelUp OnLevelUp;

	UPROPERTY(BlueprintReadWrite, BlueprintCallable, BlueprintAssignable, Category="Events")
	FEnableTracing OnEnableTracing;

	FAddScore OnAddScore;

protected:
	virtual void Init() override;

private:
	UFUNCTION(BlueprintCallable, Category="Default")
	void AddScore(const int32 Score_To_Add);

	UFUNCTION(BlueprintCallable, Category="Default")
	void HandleLevelUp();

	UFUNCTION(BlueprintCallable, Category="Default")
	void HandleEnableTracing(const bool bEnabled);

	TObjectPtr<ATileStack> Tile_Stack;
};
