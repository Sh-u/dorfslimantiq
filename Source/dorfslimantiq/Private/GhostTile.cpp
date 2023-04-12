// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostTile.h"
#include "Hexgrid.h"
#include "Inventory.h"
#include "MyGameInstance.h"
#include "ScorePopupWidget.h"
#include "TileStack.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/TextBlock.h"
#include "dorfslimantiq/Public/Utils.h"


void AGhostTile::BeginPlay() {
	Super::BeginPlay();


	Game_Instance = Cast<UMyGameInstance>(GetGameInstance());
	if (!Game_Instance) {
		UE_LOG(LogTemp, Warning, TEXT("Game Instance not found -> GhostTile."));
		return;
	}
	Tile_Stack = Cast<ATileStack>(UGameplayStatics::GetActorOfClass(this, ATileStack::StaticClass()));

	if (!Tile_Stack) return;

	Initial_SM = this->FindComponentByClass<UStaticMeshComponent>();

	UMaterial* Material = this->Initial_SM->GetMaterial(0)->GetMaterial();

	if (!Material) {
		UE_LOG(LogTemp, Warning, TEXT("No material found on ghost tile."));
		return;
	}
	Initial_Material = Material;

	Inventory = Cast<AInventory>(UGameplayStatics::GetActorOfClass(GetWorld(), AInventory::StaticClass()));

	if (!Inventory) {
		UE_LOG(LogTemp, Warning, TEXT("Inventory class must be set -> GhostTile."));
		return;
	}


	this->Initial_SM->OnBeginCursorOver.AddDynamic(this, &AGhostTile::OnMouseOver);
	this->Initial_SM->OnEndCursorOver.AddDynamic(this, &AGhostTile::OnMouseEnd);
}

void AGhostTile::Cleanup(const bool bIsDestructive) {
	Calculated_Score = 0;
	if (!Tile_Stack->Selected_Tile) return;

	Tile_Stack->OnRotateSelectedTile.RemoveDynamic(this, &AGhostTile::HandleOnRotateSelectedTile);

	TArray<AActor*> Tile_Children;
	this->GetAttachedActors(Tile_Children);
	for (const auto& Child : Tile_Children) {
		Child->Destroy();
	}

	if (!Score_Popup_Widget) {
		UE_LOG(LogTemp, Warning, TEXT("Score popup widget is not valid."));
		DBG("Score popup widget is not valid");
		return;
	}
	Score_Popup_Widget->SetVisibility(ESlateVisibility::Collapsed);

	if (bIsDestructive) {
		this->Destroy();
		return;
	}

	UStaticMeshComponent* SM = this->FindComponentByClass<UStaticMeshComponent>();
	SM->SetMaterial(0, Initial_Material);
}

void AGhostTile::OnMouseOver(UPrimitiveComponent* TouchedComponent) {
	if (!Tile_Stack->Selected_Tile) return;

	Tile_Stack->OnRotateSelectedTile.AddDynamic(this, &AGhostTile::HandleOnRotateSelectedTile);
	this->SetActorRotation(Tile_Stack->Selected_Tile->GetActorRotation());
	if (!Score_Popup_Widget) {
		TArray<UUserWidget*> Found_Widgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, Found_Widgets, UScorePopupWidget::StaticClass(), true);
		if (Found_Widgets.IsEmpty()) return;
		Score_Popup_Widget = Cast<UScorePopupWidget>(Found_Widgets[0]);
		if (!Score_Popup_Widget) {
			UE_LOG(LogTemp, Warning, TEXT("ScorePopupWidget not found -> GhostTile."));
			return;
		}
	}

	const UStaticMeshComponent* New_SM = Tile_Stack->Selected_Tile->FindComponentByClass<UStaticMeshComponent>();
	UMaterial* New_Material = New_SM->GetMaterial(0)->GetMaterial();

	if (!New_SM || !New_Material) {
		UE_LOG(LogTemp, Warning, TEXT("No sm or material"));
		return;
	}
	this->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0, New_Material);

	TArray<AActor*> Child_Actors;
	Tile_Stack->Selected_Tile->GetAllChildActors(Child_Actors);
	if (Child_Actors.IsEmpty()) {
		UE_LOG(LogTemp, Warning, TEXT("Empty selected tile actors."));
		return;
	}

	FActorSpawnParameters Spawn_Parameters;
	Spawn_Parameters.Owner = this;

	const FVector Location(0, 0, 0);
	const FRotator Rotation = FRotator(0, 0, 0);
	AActor* Spawned_Mesh_Actor = GetWorld()->SpawnActor(Child_Actors[0]->GetClass(), &Location, &Rotation,
	                                                    Spawn_Parameters);
	Spawned_Mesh_Actor->AttachToActor(this, AHexgrid::ConstructDefaultAttachmentRules());
	Spawned_Mesh_Actor->Owner = this;

	Score_Popup_Widget->Render_Location = this->GetActorLocation();
	Score_Popup_Widget->SetVisibility(ESlateVisibility::HitTestInvisible);

	FHitResult Hit;
	FVector Start = this->GetActorLocation();
	TArray<ATile*> Adjacent_Tiles;

	for (const auto& Socket_Location : Socket_Locations) {
		FVector Hit_Location = Start + Socket_Location;
		GetWorld()->LineTraceSingleByChannel(Hit, Start, Hit_Location, ECC_Visibility);
		
		if (!Hit.bBlockingHit || !IsValid(Hit.GetActor())) continue;
		
		ATile* Hit_Tile = Cast<ATile>(Hit.GetActor());
		
		if (!Hit_Tile || Hit_Tile->Tile_Type == ETiletype::Empty || Hit_Tile->Tile_Type == ETiletype::Ghost) continue;

		Adjacent_Tiles.Push(Hit_Tile);
	}

	DBG("Adjacent tiles -> %i", Adjacent_Tiles.Num());

	Calculated_Score = Game_Instance->CalculateTileScore(Tile_Stack->Selected_Tile, Adjacent_Tiles);
	Score_Popup_Widget->Score_Popup_Text->SetText(FText::FromString(FString::FromInt(Calculated_Score)));
}

void AGhostTile::OnMouseEnd(UPrimitiveComponent* TouchedComponent) {
	Cleanup(false);
}

void AGhostTile::HandleOnRotateSelectedTile() {
	this->SetActorRotation(Tile_Stack->Selected_Tile->GetActorRotation());
}
