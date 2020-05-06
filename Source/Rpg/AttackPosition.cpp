// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackPosition.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UAttackPosition::UAttackPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackPosition::BeginPlay()
{
	Super::BeginPlay();
	DrawDebugPoint(GetWorld(), GetComponentLocation(), 10.f, FColor::Red, true);
	// ...
	
}


// Called every frame
void UAttackPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

