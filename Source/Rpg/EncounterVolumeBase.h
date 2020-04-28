// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "BattleZoneBase.h"

#include "EncounterVolumeBase.generated.h"


class ADungeonCharacterBase;

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

		ADungeonCharacterBase* OverlapingPlayer = NULL;

		UFUNCTION()
		void OverlapBegin(AActor* theowner, AActor* otherActor);

		UFUNCTION()
		void OverlapEnd(AActor* theowner, AActor* otherActor);


		////Encounthre triggering
		FTimerHandle tTimerBattleTrigger;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Encountre")
		float BattleTimerRate = 0.1f;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Encountre")
			float EncountreTrigerRange = 10;

		FVector LastPlayerLoc;

		void CheckIfEncounterTrigers();
		void TriggerEncounter();
		void BattleEndTimerReset();


		/////battle area
		UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Encountre")
		ABattleZoneBase* LinkedBattleArea;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
