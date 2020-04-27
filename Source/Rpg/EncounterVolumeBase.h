// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "EncounterVolumeBase.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API AEncounterVolumeBase : public ATriggerVolume
{
	GENERATED_BODY()

public:
		AEncounterVolumeBase();

		// Called every frame
		virtual void Tick(float DeltaTime) override;


		/////Overlaps
		UFUNCTION()
		void OverlapBegin(AActor* theowner, AActor* otherActor);

		UFUNCTION()
		void OverlapEnd(AActor* theowner, AActor* otherActor);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
