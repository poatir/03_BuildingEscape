// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void AbrirPuerta();
	void CerrarPuerta();

private:
	AActor * DoorObject = nullptr;

	UPROPERTY(EditAnywhere)
	float AnguloApertura=90.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume * Trigger = nullptr;

	//AActor * ActorQueAbre;

	UPROPERTY(EditAnywhere)
	float PuertaCerrarDelay = 5.f;

	float UltimoTiempo;
	float GetTotalMassOfActorsOnPlate();
};
