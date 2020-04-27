// Fill out your copyright notice in the Description page of Project Settings.


#include "EncounterVolumeBase.h"
#include "DungeonCharacterBase.h"



AEncounterVolumeBase::AEncounterVolumeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEncounterVolumeBase::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	if (OverlapingPlayer != NULL)
	{



	}


}

void AEncounterVolumeBase::OverlapBegin(AActor* theowner, AActor* otherActor)
{

	UE_LOG(LogTemp, Warning, TEXT("Overlap Encountre"));

	if (Cast<ADungeonCharacterBase>(otherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("beginplayer overlapp"));
		OverlapingPlayer = Cast<ADungeonCharacterBase>(otherActor);
		GetWorldTimerManager().SetTimer(tTimerBattleTrigger,this, &AEncounterVolumeBase::CheckIfEncounterTrigers, BattleTimerRate, true);
	}

}

void AEncounterVolumeBase::OverlapEnd(AActor* theowner, AActor* otherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Encountre Ended"));

	if (Cast<ADungeonCharacterBase>(otherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("End over playerlap"));
		OverlapingPlayer = NULL;
		GetWorldTimerManager().ClearTimer(tTimerBattleTrigger);
	}
}


void AEncounterVolumeBase::CheckIfEncounterTrigers()
{
	if (OverlapingPlayer->GetActorLocation() != LastPlayerLoc)
	{
		LastPlayerLoc = OverlapingPlayer->GetActorLocation();
		float fRandomNo = FMath::FRandRange(0, EncountreTrigerRange);
		UE_LOG(LogTemp, Warning, TEXT("Chech if enocounter 1111,%f"), fRandomNo);
		int iRandNo = FMath::RoundToInt(fRandomNo);
		UE_LOG(LogTemp, Warning, TEXT("Chech if enocounter 22222,%i"), iRandNo);
		if (iRandNo == 1)
		{
			TriggerEncounter();
		}
	}

}

void AEncounterVolumeBase::TriggerEncounter()
{

	UE_LOG(LogTemp, Warning, TEXT("Battle Time!!!!!!!!!!"));
}

void AEncounterVolumeBase::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AEncounterVolumeBase::OverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AEncounterVolumeBase::OverlapEnd);
	
}
