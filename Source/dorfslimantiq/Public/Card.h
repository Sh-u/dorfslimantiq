#pragma once

#include "CoreMinimal.h"
#include "Card.generated.h"


enum class ETiletype : uint8;
UCLASS(Blueprintable)
class DORFSLIMANTIQ_API UCard : public UActorComponent {
	GENERATED_BODY()

public:
	UCard();

	UFUNCTION(BlueprintImplementableEvent, Category="Default")
	void ApplyCardBonus();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	TObjectPtr<UTexture2D> Image;

protected:
	virtual void BeginPlay() override;
};
