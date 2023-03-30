#pragma once

#include "CoreMinimal.h"
#include "Tiletype.generated.h"


UENUM(BlueprintType)
enum class ETiletype : uint8 {
	Empty UMETA(DisplayName= "Empty"),
	Ghost UMETA(DisplayName= "Ghost"),
	Meadow UMETA(DisplayName= "Meadow"),
	Buildings UMETA(DisplayName= "Buildings"),
	River UMETA(DisplayName= "River"),
	Mountains UMETA(DisplayName= "Mountains"),
	Forest UMETA(DisplayName = "Forest"),
	End UMETA(DisplayName = "End")
};

inline FString GetTileTypeName(ETiletype EnumValue) {
	const UEnum* EnumPtr = FindObject<UEnum>(nullptr, TEXT("/Script/dorfslimantiq.ETileType"), true);
	
	if (!EnumPtr) return FString("Invalid enum name.");

	const FString Name = EnumPtr->GetNameByValue(static_cast<uint8>(EnumValue)).ToString();
	int32 Pos = 0;
	Name.FindLastChar(':', Pos);
	return Name.RightChop(Pos + 1);
}
