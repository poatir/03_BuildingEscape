// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
	// ...
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	FVector Position;
	FRotator Rotacion;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Position, Rotacion);
	UE_LOG(LogTemp, Warning, TEXT("Posición: %s Rotación: %s"), *Position.ToString(),*Rotacion.ToString());
	FVector LineaTrazada = Position + Rotacion.Vector() * 100.0f;
	DrawDebugLine(GetWorld(),Position,LineaTrazada,FColor(255,0,0),false,0.0f,0.0f,10.f);
	// ...
}

