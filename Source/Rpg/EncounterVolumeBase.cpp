// Fill out your copyright notice in the Description page of Project Settings.


#include "EncounterVolumeBase.h"

AEncounterVolumeBase::AEncounterVolumeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEncounterVolumeBase::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);


}

void AEncounterVolumeBase::OverlapBegin(AActor* theowner, AActor* otherActor)
{

	UE_LOG(LogTemp, Warning, TEXT("Overlap Encountre"));

}

void AEncounterVolumeBase::OverlapEnd(AActor* theowner, AActor* otherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Encountre Ended"));


}


void AEncounterVolumeBase::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AEncounterVolumeBase::OverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AEncounterVolumeBase::OverlapEnd);
	
}
