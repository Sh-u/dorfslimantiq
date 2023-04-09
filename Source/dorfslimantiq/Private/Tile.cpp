// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

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

	for (const FVector& Location : Socket_Locations) {
		FVector Trace_End = Trace_Start + Location;
		GetWorld()->LineTraceSingleByChannel(Hit, Trace_Start, Trace_End, ECC_Visibility, Query_Params);
		// DrawDebugLine(GetWorld(), Trace_Start, Location, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 30.0f, 0, 10.0f);
		if (Hit.bBlockingHit || IsValid(Hit.GetActor())) {
			// UE_LOG(LogTemp, Warning, TEXT("Actor hit: %s"), *Hit.GetActor()->GetName());
			continue;
		}

		Available_Locations.Push(Trace_End);
	}

	return Available_Locations;
}

void ATile::GenerateSocketLocations() {
	const UStaticMeshComponent* Static_Mesh = this->FindComponentByClass<UStaticMeshComponent>();
	if (!Static_Mesh) {
		UE_LOG(LogTemp, Warning, TEXT("ATile -> Static mesh comp not found."));
		return;
	}
	TArray<FName> Socket_Names = Static_Mesh->GetAllSocketNames();
	if (Socket_Names.IsEmpty()) {
		UE_LOG(LogTemp, Warning, TEXT("ATile -> Socket_Names are empty."));
		return;
	}
	for (const FName& Name : Socket_Names) {
		Socket_Locations.Push(
			UKismetMathLibrary::InverseTransformLocation(Static_Mesh->GetSocketTransform(Name),
			                                             this->GetActorLocation()));
	}
}


void ATile::BeginPlay() {
	Super::BeginPlay();
	if (!Socket_Locations.IsEmpty()) return;
	GenerateSocketLocations();
}


void ATile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
