// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterDataSheet.h"
#include "BattlePawnBase.h"



// Sets default values for this component's properties
ACharacterDataSheet::ACharacterDataSheet()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ACharacterDataSheet::BeginPlay()
{
	Super::BeginPlay();
	CharactersBattleBlueprint = NewObject<ABattlePawnBase>(BattlePawnToUse);
	// ...
	
}

void ACharacterDataSheet::Tick(float DeltaTime)
{

}



