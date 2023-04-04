#pragma once
#include "CoreMinimal.h"
#include "Tiletype.h"
#include "ScoreRules.generated.h"

class ATile;

USTRUCT(BlueprintType)
struct FScoreRules {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Score;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<ETiletype, int32> Adjacent_Score;
};


UCLASS(Blueprintable)
class DORFSLIMANTIQ_API UScoreRulesBase : public UDataAsset {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Default")
	int32 CalculateTileScore(ATile* Base_Tile, TArray<ATile*> Adjacent_Tiles);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<ETiletype, FScoreRules> ScoreRules;
};
