// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterDataSheet.h"
#include "BattlePawnBase.h"
#include "AbilityBase.h"


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
	CharacterDetails.CharactersBattleBlueprint = NewObject<ABattlePawnBase>(CharacterDetails.BattlePawnToUse);
	itemsEquiped.myWeapon = NewObject<AWeaponBase>(WeaponToUse);

	for (int i = 0; i < abilityClasses.Num();i++)
	{
		abilities.Add(NewObject<UAbilityBase>(abilityClasses[i]->StaticClass()));
	}
	for (int i = 0; i < magicAbilityClasses.Num();i++)
	{
		magicAbilities.Add(NewObject<UAbilityBase>(magicAbilityClasses[i]->StaticClass()));
	}

	// ...
	
}

void ACharacterDataSheet::Tick(float DeltaTime)
{

}



