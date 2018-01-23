// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}
void UGrabber::Grab()
{
	UE_LOG(LogTemp, Error, TEXT("Grab"));
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	if (ActorHit)
	{
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true
		);
	}
		
}
void UGrabber::Release()
{
	UE_LOG(LogTemp, Error, TEXT("Release"));
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("Manejador de fisica correcto"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	if (!InputComponente)
	{
		InputComponente = GetOwner()->FindComponentByClass<UInputComponent>();
		if (InputComponente)
		{
			UE_LOG(LogTemp, Warning, TEXT("Input component encontrado"));
			InputComponente->BindAction("Grab_Mapping", IE_Pressed, this, &UGrabber::Grab);
			InputComponente->BindAction("Grab_Mapping", IE_Released, this, &UGrabber::Release);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Falta input component"));
		}
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	UE_LOG(LogTemp, Warning, TEXT("Posición: %s Rotación: %s"), *PlayerViewPointLocation.ToString(),*PlayerViewPointRotation.ToString());
	FVector LineaTrazada = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * 100.0f;
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineaTrazada, FColor(255, 0, 0), false, 0.0f, 0.0f, 10.f);
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineaTrazada,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("LineTraceHit: %s"), *(ActorHit->GetName()));
	}
	return Hit;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	
}
// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	if (UnaVez == false)
	{
		SetupInputComponent();
		UnaVez = true;
	}
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Posición: %s Rotación: %s"), *PlayerViewPointLocation.ToString(),*PlayerViewPointRotation.ToString());
	FVector LineaTrazada = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * 200.0f;
	if (PhysicsHandle->GrabbedComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Objeto cogido"));
		PhysicsHandle->SetTargetLocation(LineaTrazada);
	}

}

