// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

// Sets default values for this component's properties
AWeaponBase::AWeaponBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ...
}

