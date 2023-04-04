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



inline FString GetTileTypeName(ETiletype Enum_Value) {
	const UEnum* Enum_Ptr = FindObject<UEnum>(nullptr, TEXT("/Script/dorfslimantiq.ETileType"), true);
	
	if (!Enum_Ptr) return FString("Invalid enum name.");

	const FString Name = Enum_Ptr->GetNameByValue(static_cast<uint8>(Enum_Value)).ToString();
	int32 Pos = 0;
	Name.FindLastChar(':', Pos);
	return Name.RightChop(Pos + 1);
}
