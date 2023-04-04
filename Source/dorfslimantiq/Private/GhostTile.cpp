// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostTile.h"
#include "Hexgrid.h"
#include "ScorePopupWidget.h"
#include "ScoreRules.h"
#include "TileStack.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/TextBlock.h"
#include "dorfslimantiq/Public/Utils.h"


void AGhostTile::BeginPlay() {
	Super::BeginPlay();

	Tile_Stack = Cast<ATileStack>(UGameplayStatics::GetActorOfClass(this, ATileStack::StaticClass()));

	if (!Tile_Stack) return;

	Initial_SM = this->FindComponentByClass<UStaticMeshComponent>();

	UMaterial* Material = this->Initial_SM->GetMaterial(0)->GetMaterial();

	if (!Material) {
		UE_LOG(LogTemp, Warning, TEXT("No material found on ghost tile."));
		return;
	}
	Initial_Material = Material;

	this->Initial_SM->OnBeginCursorOver.AddDynamic(this, &AGhostTile::OnMouseOver);
	this->Initial_SM->OnEndCursorOver.AddDynamic(this, &AGhostTile::OnMouseEnd);
}


void AGhostTile::OnMouseOver(UPrimitiveComponent* TouchedComponent) {
	if (!Tile_Stack->Selected_Tile) return;
	UE_LOG(LogTemp, Warning, TEXT("Enter."));
	Tile_Stack->OnRotateSelectedTile.AddDynamic(this, &AGhostTile::HandleOnRotateSelectedTile);
	this->SetActorRotation(Tile_Stack->Selected_Tile->GetActorRotation());
	if (!Score_Popup_Widget) {
		UE_LOG(LogTemp, Warning, TEXT("Not found score popup widget."));
		TArray<UUserWidget*> Found_Widgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, Found_Widgets, UScorePopupWidget::StaticClass(), true);
		if (Found_Widgets.IsEmpty()) return;
		Score_Popup_Widget = Cast<UScorePopupWidget>(Found_Widgets[0]);
	}


	const UStaticMeshComponent* New_SM = Tile_Stack->Selected_Tile->FindComponentByClass<UStaticMeshComponent>();
	UMaterial* New_Material = New_SM->GetMaterial(0)->GetMaterial();

	if (!New_SM || !New_Material) {
		UE_LOG(LogTemp, Warning, TEXT("No sm or material"));
		return;
	}
	this->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0, New_Material);

	TArray<AActor*> ChildActors;
	Tile_Stack->Selected_Tile->GetAllChildActors(ChildActors);
	if (ChildActors.IsEmpty()) {
		UE_LOG(LogTemp, Warning, TEXT("Empty selected tile actors."));
		return;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	const FVector Location(0, 0, 0);
	const FRotator Rotation = FRotator(0, 0, 0);
	AActor* Spawned_Mesh_Actor = GetWorld()->SpawnActor(ChildActors[0]->GetClass(), &Location, &Rotation,
	                                                    SpawnParameters);
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
		// DrawDebugLine(GetWorld(), Start, Hit_Location, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
		if (!Hit.bBlockingHit || !IsValid(Hit.GetActor())) continue;
		ATile* Hit_Tile = Cast<ATile>(Hit.GetActor());
		DBG("Hit actor: %s, Type: %s", *Hit.GetActor()->GetName(), *GetTileTypeName(Hit_Tile->Tile_Type));
		if (!Hit_Tile || Hit_Tile->Tile_Type == ETiletype::Empty || Hit_Tile->Tile_Type == ETiletype::Ghost) continue;
		Adjacent_Tiles.Push(Hit_Tile);
	}

	if (Adjacent_Tiles.IsEmpty()) {
		DBG("No adjacent tiles");
		return;
	}

	if (!Score_Rules) {
		UE_LOG(LogTemp, Warning, TEXT("Score rules not found log."));
		DBG("Score rules not found");
		return;
	}
	int32 Score = Score_Rules->CalculateTileScore(Tile_Stack->Selected_Tile, Adjacent_Tiles);
	Score_Popup_Widget->Score_Popup_Text->SetText(FText::FromString(FString::FromInt(Score)));
}

void AGhostTile::OnMouseEnd(UPrimitiveComponent* TouchedComponent) {
	UE_LOG(LogTemp, Warning, TEXT("End."));
	Tile_Stack->OnRotateSelectedTile.RemoveDynamic(this, &AGhostTile::HandleOnRotateSelectedTile);
	UStaticMeshComponent* SM = this->FindComponentByClass<UStaticMeshComponent>();

	TArray<AActor*> Tile_Children;
	this->GetAttachedActors(Tile_Children);
	for (const auto& Child : Tile_Children) {
		Child->Destroy();
	}


	SM->SetMaterial(0, Initial_Material);

	Score_Popup_Widget->SetVisibility(ESlateVisibility::Collapsed);
}

void AGhostTile::HandleOnRotateSelectedTile() {
	this->SetActorRotation(Tile_Stack->Selected_Tile->GetActorRotation());
}
