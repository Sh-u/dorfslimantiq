#include "ScoreRules.h"
#include "Tile.h"


int32 UScoreRulesBase::CalculateTileScore(ATile* Base_Tile, TArray<ATile*> Adjacent_Tiles) {
	const ETiletype Tiletype = Base_Tile->Tile_Type;
	const FScoreRules* Base_Tile_Rules = ScoreRules.Find(Tiletype);
	int32 Score = Base_Tile_Rules->Score;
	for (const auto& Tile : Adjacent_Tiles) {
		if (const auto Calc_Score = Base_Tile_Rules->Adjacent_Score.Find(Tile->Tile_Type)) {
			Score += *Calc_Score;
		}
		
	}

	return Score;
}
