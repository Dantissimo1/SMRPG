// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticleHolder.h"
#include "BattlePawnBase.h"


// Sets default values
AParticleHolder::AParticleHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AParticleHolder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AParticleHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParticleHolder::SetUp(ABattlePawnBase* inOwner)
{
	myOwner = inOwner;
}

void AParticleHolder::DoAbilityDamage()
{
	myOwner->doAbilityDamage = true;
}

void AParticleHolder::AnimEnd()
{
	myOwner->abilityAnimDone = true;
}

