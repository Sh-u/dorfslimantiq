#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Card.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DORFSLIMANTIQ_API UCard : public UActorComponent {
	GENERATED_BODY()

public:
	UCard();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	TObjectPtr<UTexture2D> Image;

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category="Default")
	virtual int32 ApplyCardBonus() { return 0; }

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
