// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"


ATile::ATile() {
	PrimaryActorTick.bCanEverTick = true;
}

TArray<FVector> ATile::GenerateAvailableSpawnLocations() {
	TArray<FVector> Available_Locations;

	if (Socket_Locations.IsEmpty()) return Available_Locations;

	FHitResult Hit;
	FVector Trace_Start = GetActorLocation();
	FCollisionQueryParams Query_Params;
	Query_Params.AddIgnoredActor(this);
	// UE_LOG(LogTemp, Warning, TEXT("This tile location: %s"), *Trace_Start.ToString());
	for (const FVector& Location : Socket_Locations) {
		// UE_LOG(LogTemp, Warning, TEXT("Socket locations: %s"), *Location.ToString());
		GetWorld()->LineTraceSingleByChannel(Hit, Trace_Start, Location, ECC_Visibility, Query_Params);
		// DrawDebugLine(GetWorld(), Trace_Start, Location, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 30.0f, 0, 10.0f);
		if (Hit.bBlockingHit || IsValid(Hit.GetActor())) {
			// UE_LOG(LogTemp, Warning, TEXT("Actor hit: %s"), *Hit.GetActor()->GetName());
			continue;
		}
		
		Available_Locations.Push(Location);
	}

	return Available_Locations;
}

void ATile::GenerateSocketLocations() {
	const UStaticMeshComponent* Static_Mesh = this->FindComponentByClass<UStaticMeshComponent>();
	if (!Static_Mesh)return;
	TArray<FName> Socket_Names = Static_Mesh->GetAllSocketNames();
	if (Socket_Names.IsEmpty()) return;
	for (const FName& Name : Socket_Names) {
		Socket_Locations.Push(Static_Mesh->GetSocketLocation(Name));
	}
}


void ATile::BeginPlay() {
	Super::BeginPlay();
}


void ATile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
