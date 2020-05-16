// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPartyFormationCompnent.h"

// Sets default values for this component's properties
AEnemyPartyFormationCompnent::AEnemyPartyFormationCompnent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;

	//////set initial lengh of avlible party slots do not add more under any circomstance
	PartyFormationFrontLineSub.Add(NULL);
	PartyFormationFrontLineSub.Add(NULL);
	PartyFormationFrontLineSub.Add(NULL);
	PartyFormationFrontLineSub.Add(NULL);

	PartyFormationBackLineSub.Add(NULL);
	PartyFormationBackLineSub.Add(NULL);
	PartyFormationBackLineSub.Add(NULL);
	PartyFormationBackLineSub.Add(NULL);

	// ...
}


// Called when the game starts
void AEnemyPartyFormationCompnent::BeginPlay()
{
	Super::BeginPlay();
	//////////////UE_LOG(LogTemp, Warning, TEXT("Enemy party comp exists"));
	
	// ...
	
}


// Called every frame
void AEnemyPartyFormationCompnent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ...
}

