// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"
#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;
	TArray<AActor*> OverlappingActors;
	if (!Trigger) { return TotalMass; }
	Trigger->GetOverlappingActors(OUT OverlappingActors);
	for (const auto& Actor: OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	DoorObject = GetOwner();
	//ActorQueAbre = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!Trigger)
	{
		UE_LOG(LogTemp, Error, TEXT("No hay volumen Trigger"));
	}
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	
	//if (Trigger->IsOverlappingActor(ActorQueAbre))
	if (GetTotalMassOfActorsOnPlate() > 60.f)
	{
		AbrirPuerta();
		UltimoTiempo = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetTimeSeconds() - UltimoTiempo > this->PuertaCerrarDelay)
	{
		CerrarPuerta();
	}
	
}

void UOpenDoor::AbrirPuerta()
{
	OnOpenRequest.Broadcast();
	//DoorObject->SetActorRotation(FRotator(0.0f, AnguloApertura, 0.0f));
}
void UOpenDoor::CerrarPuerta()
{
	OnCloseRequest.Broadcast();
	//DoorObject->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

