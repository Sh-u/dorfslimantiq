#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Card.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DORFSLIMANTIQ_API UCard : public UActorComponent {
	GENERATED_BODY()

public:
	UCard();

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category="Default")
	virtual void CalculateScore() {
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	UTexture2D* Image;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
