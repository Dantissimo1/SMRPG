// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPartyFormationList.h"
#include "EnemyPartyFormationCompnent.h"


// Sets default values
AEnemyPartyFormationList::AEnemyPartyFormationList()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyPartyFormationList::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyPartyFormationList::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

