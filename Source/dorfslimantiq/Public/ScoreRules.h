#pragma once
#include "CoreMinimal.h"
#include "Tiletype.h"
#include "ScoreRules.generated.h"

USTRUCT(BlueprintType)
struct FScoreRules {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ETiletype, int32> Adjacent_Score;
};
